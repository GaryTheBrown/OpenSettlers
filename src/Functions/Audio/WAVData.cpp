/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "WAVData.h"

void Functions::WAVData::SaveToFile(std::string filename){
	// mimeType = "audio/wav";
	unsigned char Header[44] = {

			'R','I','F','F',		//File description header	4 bytes (DWord)	The ASCII text string "RIFF" The procedure converiting 4-symbol string into dword is included in unit Wave
			0,0,0,0,				//Size of file	4 bytes (DWord)	The file size not including the "RIFF" description (4 bytes) and file description (4 bytes). This is file size - 8.
			'W','A','V','E',		//WAV description header	4 bytes (DWord)	The ASCII text string "WAVE"
			'f','m','t',' ',		//Format description header	4 bytes (DWord)	The ASCII text string "fmt "(The space is also included)
			0x10,0x00,0x00,0x00,	//Size of WAVE section chunck	4 bytes (DWord)	The size of the WAVE type format (2 bytes) + mono/stereo flag (2 bytes) + sample rate (4 bytes) + bytes per sec (4 bytes) + block alignment (2 bytes) + bits per sample (2 bytes). This is usually 16.
			0,0,					//WAVE type format	2 bytes (Word)	Type of WAVE format. This is a PCM header = $01 (linear quntization). Other values indicates some forms of compression.
			0,0,					//Number of channels	2 bytes (Word)	mono ($01) or stereo ($02). You may try more channels...
			0,0,0,0,				//Samples per second	4 bytes (DWord)	The frequency of quantization (usually 44100 Hz, 22050 Hz, ...)
			0,0,0,0,				//Bytes per second	4 bytes (DWord)	Speed of data stream = Number_of_channels*Samples_per_second*Bits_per_Sample/8
			0,0,					//Block alignment	2 bytes (Word)	Number of bytes in elementary quantization = Number_of_channels*Bits_per_Sample/8
			0,0,					//Bits per sample	2 bytes (Word)	Digits of quantization (usually 32, 24, 16, 8). I wonder if this is, for example, 5 ..?
			'd','a','t','a',		//Data description header	4 bytes (DWord)	The ASCII text string "data".
			0,0,0,0					//Size of data	4 bytes (DWord)	Number of bytes of data is included in the data section.
	};

	unsigned int FileSize = (this->length - 20) + 36;
	Header[4] = (unsigned char)(FileSize    ) & 0xFF;
	Header[5] = (unsigned char)(FileSize>> 8) & 0xFF;
	Header[6] = (unsigned char)(FileSize>>16) & 0xFF;
	Header[7] = (unsigned char)(FileSize>>24) & 0xFF;


	Header[20] = (unsigned char)this->fileVersion & 0xFF;
	Header[22] = (unsigned char)this->channels & 0xFF;

	Header[24] = (unsigned char)(this->samplesPerSecond    ) & 0xFF;
	Header[25] = (unsigned char)(this->samplesPerSecond>> 8) & 0xFF;
	Header[26] = (unsigned char)(this->samplesPerSecond>>16) & 0xFF;
	Header[27] = (unsigned char)(this->samplesPerSecond>>24) & 0xFF;

	Header[28] = (unsigned char)(this->bytesPerSecond    ) & 0xFF;
	Header[29] = (unsigned char)(this->bytesPerSecond>> 8) & 0xFF;
	Header[30] = (unsigned char)(this->bytesPerSecond>>16) & 0xFF;
	Header[31] = (unsigned char)(this->bytesPerSecond>>24) & 0xFF;

	Header[32] = (unsigned char)this->blockAlignment & 0xFF;
	Header[34] = (unsigned char)this->bitsPerSample & 0xFF;

	Header[40] = (unsigned char)((this->length-20)    ) & 0xFF;
	Header[41] = (unsigned char)((this->length-20)>> 8) & 0xFF;
	Header[42] = (unsigned char)((this->length-20)>>16) & 0xFF;
	Header[43] = (unsigned char)((this->length-20)>>24) & 0xFF;

	if(Functions::FileExists(filename))
		remove(filename.c_str());

	std::ofstream ofile;
	ofile.open(filename.c_str(),std::ios::binary);
	ofile.write((char*)Header, sizeof(Header));
	ofile.write((char*)this->data,(length-20));
	ofile.close();
}

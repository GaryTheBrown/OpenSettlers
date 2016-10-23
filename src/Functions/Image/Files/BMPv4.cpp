/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "../FileImage.h"

void Functions::FileImage::SaveToRGBBMPv4(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height){
	// mimeType = "image/bmp";
	unsigned char file[14] = {
			'B','M', // magic
			0,0,0,0, // size in bytes
			0,0, // app data xRel for us
			0,0, // app data yRel for us
			122,0,0,0 // start of data offset
	};

	unsigned char info[108] = {
			0x6C,0x00,0x00,0x00,	//108 bytes	Number of bytes in the DIB header (from this point)
			0x00,0x00,0x00,0x00,	//4 pixels (left to right order)	Width of the bitmap in pixels
			0x00,0x00,0x00,0x00,	//2 pixels (bottom to top order)	Height of the bitmap in pixels
			0x01,0x00,				//1 plane	Number of color planes being used
			0x20,0x00,				//32 bits	Number of bits per pixel
			0x03,0x00,0x00,0x00,	//3 Compression used (BI_BITFIELDS)
			0x00,0x00,0x00,0x00,	//0	Size of the raw bitmap data (including padding)
			0x00,0x00,0x00,0x00,	//2835 pixels/meter horizontal	Print resolution of the image,72 DPI × 39.3701 inches per meter yields 2834.6472
			0x00,0x00,0x00,0x00,	//2835 pixels/meter vertical
			0x00,0x00,0x00,0x00,	//0 colors	Number of colors in the palette
			0x00,0x00,0x00,0x00,	//0 important colors	0 means all colors are important

			0x00,0x00,0xFF,0x00,	//00FF0000 in big-endian	Red channel bit mask (valid because BI_BITFIELDS is specified)
			0x00,0xFF,0x00,0x00,	//0000FF00 in big-endian	Green channel bit mask (valid because BI_BITFIELDS is specified)
			0xFF,0x00,0x00,0x00,	//000000FF in big-endian	Blue channel bit mask (valid because BI_BITFIELDS is specified)
			0x00,0x00,0x00,0xFF,	//FF000000 in big-endian	Alpha channel bit mask

			0x00,0x00,0x00,0x00,	// COLOR SPACE
			0x00,0x00,0x00,0x00,	// X coordinate of red endpoint
			0x00,0x00,0x00,0x00,	// Y coordinate of red endpoint
			0x00,0x00,0x00,0x00,	// Z coordinate of red endpoint
			0x00,0x00,0x00,0x00,	// X coordinate of green endpoint
			0x00,0x00,0x00,0x00,	// Y coordinate of green endpoint
			0x00,0x00,0x00,0x00,	// Z coordinate of green endpoint
			0x00,0x00,0x00,0x00,	// X coordinate of blue endpoint
			0x00,0x00,0x00,0x00,	// Y coordinate of blue endpoint
			0x00,0x00,0x00,0x00,	// Z coordinate of blue endpoint
			0x00,0x00,0x00,0x00,	// Gamma red coordinate scale value
			0x00,0x00,0x00,0x00,	// Gamma green coordinate scale value
			0x00,0x00,0x00,0x00		// Gamma blue coordinate scale value
	};

	int sizeData = width*height*4;
	int sizeAll  = sizeData + sizeof(file) + sizeof(info);

	file[2] = (unsigned char)(sizeAll) & 0xFF;
	file[3] = (unsigned char)(sizeAll>> 8) & 0xFF;
	file[4] = (unsigned char)(sizeAll>>16) & 0xFF;
	file[5] = (unsigned char)(sizeAll>>24) & 0xFF;

	info[4] = (unsigned char)(width) & 0xFF;
	info[5] = (unsigned char)(width>> 8) & 0xFF;
	info[6] = (unsigned char)(width>>16) & 0xFF;
	info[7] = (unsigned char)(width>>24) & 0xFF;

	info[8] = (unsigned char)(height) & 0xFF;
	info[9] = (unsigned char)(height>> 8) & 0xFF;
	info[10] = (unsigned char)(height>>16) & 0xFF;
	info[11] = (unsigned char)(height>>24) & 0xFF;

	//Check File Doesn't Exist if it does delete it
	if(FileExists(filename))
		remove(filename.c_str());

	std::ofstream ofile;
	//open the ofile
	ofile.open(filename.c_str(),std::ios::binary);

	//Write Header Info To File
	ofile.write((char*)file, sizeof(file));
	ofile.write((char*)info, sizeof(info));

	//Write Pixel Data To File (bottom to top)
	int pixel = 0;
	for (unsigned short y=height; y>0; y-- ){
		for (unsigned short x=0; x<width; x++ ){
			pixel = ((y - 1) * width) + x;

			unsigned char outPixel[4];
			outPixel[0] = imageRGBA[pixel].B; //Red
			outPixel[1] = imageRGBA[pixel].G; //Green
			outPixel[2] = imageRGBA[pixel].R; //Blue
			outPixel[3] = imageRGBA[pixel].A; //Alpha

			ofile.write((char*)outPixel,4);
		}
	}

	//Close The File
	ofile.close();
}

RGBA* Functions::FileImage::LoadBMPv4ToRGBA(DataReader* reader, unsigned short* width, unsigned short* height){

	reader->MoveOffset(4);
	*width = (reader->ReadInt() & 0xFFFF);
	*height = (reader->ReadInt() & 0xFFFF);
	reader->MoveOffset(2);
	int bitsPerPixel = reader->ReadShort();
	reader->MoveOffset(92);

	char padding = ((bitsPerPixel/8) * (*width))%4;

	RGBA* imageRGBA = new RGBA[(*height)*(*width)];

	RGBA palette[256];

	if (bitsPerPixel == 8){
		//Read Palette
		for (int i = 0; i < 256; i++){
			palette[i].B = reader->ReadChar();
			palette[i].G = reader->ReadChar();
			palette[i].R = reader->ReadChar();
			palette[i].A = reader->ReadChar();
		}
	}

	int pixel = 0;
	for (unsigned short y=(*height); y>0; y-- ){
		for (unsigned short x=0; x<(*width); x++ ){
			pixel = ((y - 1) * (*width)) + x;

			if (bitsPerPixel == 8){
				unsigned char singlePixel = reader->ReadChar();
				imageRGBA[pixel].B = palette[singlePixel].B;
				imageRGBA[pixel].G = palette[singlePixel].G;
				imageRGBA[pixel].R = palette[singlePixel].R;
				imageRGBA[pixel].A = palette[singlePixel].A;
			}
			if (bitsPerPixel == 24){
				imageRGBA[pixel].B = reader->ReadChar();
				imageRGBA[pixel].G = reader->ReadChar();
				imageRGBA[pixel].R = reader->ReadChar();
				imageRGBA[pixel].A = 255;
			}
			if (bitsPerPixel == 32){
				imageRGBA[pixel].B = reader->ReadChar();
				imageRGBA[pixel].G = reader->ReadChar();
				imageRGBA[pixel].R = reader->ReadChar();
				imageRGBA[pixel].A = reader->ReadChar();
			}
			//check padding and skip it.
			for (char i=0; i<padding; i++)
				reader->ReadChar();
		}
	}

	reader->~DataReader();
	return imageRGBA;
}

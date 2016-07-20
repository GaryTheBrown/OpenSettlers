/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "BOBDataType.h"

Extractor::Settlers2::BOBDataType::BOBDataType(std::string file){

	if (Functions::FileExists(file) == true){
		Functions::DataReader* reader = new Functions::DataReader(file);

		//Make Sure File Is at 0
		reader->SetOffset(0);

		//Set Big Endian Mode ??
		//reader->SetBigEndian();

		this->size = reader->ReadShort();

		this->rawBase = new unsigned char[this->size];
		for (unsigned short i = 0; i < this->size; i++)
			this->rawBase[i] = reader->ReadChar();

		this->rawBaseHeight = this->size/this->rawBaseWidth;

		for(unsigned int i = 0; i < 96; i++){
			unsigned char* newImage = new unsigned char[this->size];
			for (unsigned short i = 0; i < this->size; i++)
				newImage[i] = this->rawBase[i];

			unsigned short id = reader->ReadShort();
			unsigned char height = reader->ReadChar();

			unsigned int offset = reader->GetOffset();
			unsigned int* starts = new unsigned int[height];
			for (unsigned short i = 0; i < height; i++)
				starts[i] = offset + reader->ReadShort();

			unsigned char ny = reader->ReadChar();
			this->image[i] = new PlayerColouredBitmap(reader,32,height,16,ny,newImage,starts,true);
		}

		for(unsigned int i = 0; i < 6; i++){
			unsigned short id = reader->ReadShort();
			this->raw[i].first = reader->ReadShort();

			this->raw[i].second = new unsigned char[this->raw[i].first];
			for(unsigned int j = 0; j < this->raw[i].first; j++)
				this->raw[i].second[j] = reader->ReadChar();
		}
	}
}
Extractor::Settlers2::BOBDataType::~BOBDataType() {

}

void Extractor::Settlers2::BOBDataType::SaveToFile(std::string location){
	location += "/";
	RGBA* RGBImage = Functions::ConvertPALToRGBA(this->rawBase,NULL,this->Palette,this->size);
	Functions::FileImage* fileImage = new Functions::FileImage();
	fileImage->SaveToPaletteImage(location + "BASE.PAL.bmp",this->rawBase,this->Palette,this->rawBaseWidth,this->rawBaseHeight);
	fileImage->SaveToRGBImage(location + "BASE.RGB.bmp",RGBImage,this->rawBaseWidth,this->rawBaseHeight);
	delete fileImage;

}


/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "FontData.h"

Extractor::Settlers2::FontData::FontData(Functions::DataReader* reader) {
	this->xSpacing = reader->ReadChar();
	this->ySpacing = reader->ReadChar();

	//TODO Finish this
	//how is this data stored?
	short size = this->xSpacing + this->ySpacing;
	for (unsigned char i = 0; i < this->count; i++){
		this->ImageData[i] = new unsigned char[size];
		for (unsigned short j = 0; j < size; j++){
			this->ImageData[i][j] = reader->ReadChar();
		}
	}
}

Extractor::Settlers2::FontData::~FontData() {
	for (unsigned char i = 0; i < this->count; i++){
		delete [] this->ImageData[i];
	}
}

void Extractor::Settlers2::FontData::SaveFileData(std::string location){
	location += "/";
	Functions::CreateDir(location);
	for (unsigned char i = 0; i < this->count; i++){
		//TODO FOr each imagedata[i] save the file
		//need to grab the palette from somewhere for this.
	}
}

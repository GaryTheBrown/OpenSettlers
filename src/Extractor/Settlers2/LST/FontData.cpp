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

	unsigned int size = this->xSpacing + this->ySpacing;
	for (unsigned int i = 0; i < this->count; i++){
		this->imageData[i] = new unsigned char[size];
		for (unsigned int j = 0; j < size; j++){
			this->imageData[i][j] = reader->ReadChar();
		}
	}
}

Extractor::Settlers2::FontData::~FontData() {
	for (unsigned int i = 0; i < this->count; i++){
		delete [] this->imageData[i];
	}
}

void Extractor::Settlers2::FontData::SaveToFile(std::string filename){
	std::string data = "";
	data += "xSpacing=" + Functions::ToString((int)this->xSpacing) + "\n";
	data += "ySpacing=" + Functions::ToString((int)this->ySpacing) + "\n";
	Functions::SaveToTextFile(filename + ".txt",data);

	filename.append("/");
	Functions::CreateDir(filename);
	Functions::FileImage* fileImage = new Functions::FileImage();
	for (unsigned int i = 0; i < this->count; i++){
		//fileImage->SaveToRGBImage(filename,this->ConvertToRGBA(),this->width,this->height);

		fileImage->SaveToPaletteImage(filename + Functions::ToString(i + 32) + ".bmp",this->imageData[i],this->palette,this->ySpacing,this->xSpacing);
	}
	delete fileImage;
}

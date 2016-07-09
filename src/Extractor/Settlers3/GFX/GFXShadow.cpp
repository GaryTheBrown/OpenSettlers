/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "GFXShadow.h"

Extractor::Settlers3::GFXShadow::GFXShadow(Functions::DataReader* reader, unsigned int offset){
	reader->SetOffset(offset);
	this->headerID = reader->ReadInt();
	this->headerSize = reader->ReadShort();
	this->count = reader->ReadShort();

	if (this->count>0){
		unsigned int offsets[this->count];
		for (unsigned short i = 0;i < this->count;i++){
			offsets[i] = reader->ReadInt();
		}

		this->images = new RGBFrameData*[this->count];
		for (unsigned short i = 0;i < this->count;i++){
			this->images[i] = new RGBFrameData(reader,offsets[i],RGBImageData::IMG_GFX_Shadow);
		}
	}
}

Extractor::Settlers3::GFXShadow::~GFXShadow(){
	if(this->images != NULL){
		for (unsigned short i = 0; i < this->count; i++){
			delete this->images[i];
		}
		delete[] this->images;
	}
}

bool Extractor::Settlers3::GFXShadow::SaveFileData(std::string location){
	if(this->count > 0){
		location += "/Shadow/";
		Functions::CreateDir(location);
		for(unsigned short i = 0; i < this->count; i++){
			if(this->images[i] != NULL) this->images[i]->SaveFileData(location + Functions::ToString(i));
		}
		return true;
	}
	return false;
}

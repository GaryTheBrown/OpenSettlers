/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "ShadowBitmap.h"
Extractor::Settlers2::ShadowBitmap::ShadowBitmap(Functions::DataReader* reader){

	this->xRel = reader->ReadSignedShort();
	this->yRel = reader->ReadSignedShort();
	reader->MoveOffset(4);
	this->width = reader->ReadShort();
	this->height = reader->ReadShort();
	reader->MoveOffset(6);

	unsigned int imageSize = this->height*this->width;
	this->imageRGBA = new RGBA[imageSize];

	reader->MoveOffset(this->height*2);

	for (unsigned int i = 0; i < imageSize;){
		unsigned char code = reader->ReadChar();
		if (code < 0xFF){
			for (unsigned char j = 0; j < code; i++,j++){
				this->imageRGBA[i] = {0,0,0,127};
			}
			code = reader->ReadChar();
			if (code < 0xFF){
				for (unsigned char j = 0; j < code; i++,j++){
					this->imageRGBA[i] = {0,0,0,0};
				}
			}
		}
	}
}

void Extractor::Settlers2::ShadowBitmap::SaveToFile(std::string filename){
	std::string data = "";
	data += "Width=" + Functions::ToString(this->width) + "\n";
	data += "Height=" + Functions::ToString(this->height) + "\n";
	data += "OffsetPositionX=" + Functions::ToString(this->xRel) + "\n";
	data += "OffsetPositionY=" + Functions::ToString(this->yRel) + "\n";
	Functions::SaveToTextFile(filename + ".txt",data);
	RGBImage::SaveToFile(filename);
}

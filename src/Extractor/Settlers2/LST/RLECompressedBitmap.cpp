/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "RLECompressedBitmap.h"
//TODO Fix errors in this system
Extractor::Settlers2::RLECompressedBitmap::RLECompressedBitmap(Functions::DataReader* reader){
	this->xRel = reader->ReadSignedShort();
	this->yRel = reader->ReadSignedShort();
	this->unknown = reader->ReadInt();
	this->width = reader->ReadShort();
	this->height = reader->ReadShort();
	this->paletteID = reader->ReadShort();
	this->partSize = reader->ReadInt();

	unsigned int imageSize = this->height*this->width;
	this->image = new unsigned char[imageSize];
	this->transparency = new bool[imageSize];
//TMP
	unsigned int offset = reader->GetOffset();

	this->tempData = new unsigned char[this->partSize];
	for(unsigned int i = 0; i < this->partSize; i++){
		this->tempData[i] = reader->ReadChar();
	}

	reader->SetOffset(offset);
//ENDTMP
	reader->MoveOffset(this->height*2);

	for (unsigned int i = 0; i < imageSize;){
		unsigned char code = reader->ReadChar();
		if (code < 0xFF){
			for (unsigned char j = 0; j < code; i++,j++){
				this->image[i] = reader->ReadChar();
			}
			code = reader->ReadChar();
			if (code < 0xFF){
				for (unsigned char j = 0; j < code; i++,j++){
					this->transparency[i] = true;
				}
			}
		}
	}
}
//TMP Feature
void Extractor::Settlers2::RLECompressedBitmap::SaveToFile(std::string filename){
	PaletteImage::SaveToFile(filename);
	Functions::SaveToBinaryFile(filename + ".dat",(char*)this->tempData,this->partSize);
}

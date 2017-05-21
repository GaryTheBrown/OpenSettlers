/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "RLECompressedBitmap.h"

Extractor::Settlers2::RLECompressedBitmap::RLECompressedBitmap(Functions::DataReader* reader){
	this->xRel = reader->ReadSignedShort();
	this->yRel = reader->ReadSignedShort();
	reader->MoveOffset(4);
	this->width = reader->ReadShort();
	this->height = reader->ReadShort();
	reader->MoveOffset(6);

	unsigned int imageSize = this->height*this->width;
	this->image = new unsigned char[imageSize];
	for (unsigned int i = 0; i < imageSize; i++){
		this->image[i] = 0;
	}
	this->transparency = new bool[imageSize];
	for (unsigned int i = 0; i < imageSize; i++){
		this->transparency[i] = false;
	}

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

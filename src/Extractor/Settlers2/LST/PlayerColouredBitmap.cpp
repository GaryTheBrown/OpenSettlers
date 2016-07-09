/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "PlayerColouredBitmap.h"

Extractor::Settlers2::PlayerColouredBitmap::PlayerColouredBitmap(Functions::DataReader* reader){
	this->xRel = reader->ReadSignedShort();
	this->yRel = reader->ReadSignedShort();
	this->unknown = reader->ReadInt();
	this->width = reader->ReadShort();
	this->height = reader->ReadShort();
	this->paletteID = reader->ReadShort();
	this->partSize = reader->ReadInt();

	//this->image = new unsigned char[this->width*this->height];
	this->image = new unsigned char[this->partSize];
	for (unsigned int i = 0; i < this->partSize; i++)
		this->image[i] = reader->ReadChar();
	this->tmpsize = partSize;
}

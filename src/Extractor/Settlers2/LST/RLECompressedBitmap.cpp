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

Extractor::Settlers2::RLECompressedBitmap::RLECompressedBitmap(Functions::DataReader* reader){
	this->zeroPointX = reader->ReadSignedShort();
	this->zeroPointY = reader->ReadSignedShort();
	this->unknown = reader->ReadInt();
	this->width = reader->ReadShort();
	this->height = reader->ReadShort();
	this->paletteID = reader->ReadShort();

	this->image = new unsigned char[this->width*this->height];

}

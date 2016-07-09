/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "UncompressedBitmap.h"

Extractor::Settlers2::UncompressedBitmap::UncompressedBitmap(Functions::DataReader* reader) {
	this->paletteID = reader->ReadShort(); //(always 1 = hex 01 00)
	this->lengthOfData = reader->ReadInt();

	//A raw paletted 8-bit bitmap, pixel-by-pixel.
	this->image = new unsigned char[this->lengthOfData];

	for (unsigned int i = 0; i < this->lengthOfData; i++)
		this->image[i] = reader->ReadChar();

	//Footer
	this->zeroPointX = reader->ReadShort();
	this->zeroPointY = reader->ReadShort();
	this->width = reader->ReadShort();
	this->height = reader->ReadShort();
	this->unknown = reader->ReadLongLong();
}

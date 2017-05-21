/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "UncompressedBitmap.h"

Extractor::Settlers2::UncompressedBitmap::UncompressedBitmap(Functions::DataReader* reader) {
	reader->MoveOffset(2);
	unsigned int lengthOfData = reader->ReadInt();

	//A raw paletted 8-bit bitmap, pixel-by-pixel.
	this->image = new unsigned char[lengthOfData];

	for (unsigned int i = 0; i < lengthOfData; i++)
		this->image[i] = reader->ReadChar();

	//Footer
	this->xRel = reader->ReadSignedShort();
	this->yRel = reader->ReadSignedShort();
	this->width = reader->ReadShort();
	this->height = reader->ReadShort();
	reader->MoveOffset(8);
}

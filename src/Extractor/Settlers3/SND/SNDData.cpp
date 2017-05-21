/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "SNDData.h"

Extractor::Settlers3::SNDData::SNDData(Functions::DataReader* reader, unsigned int offset) {
	reader->SetOffset(offset);

	this->length = reader->ReadInt();
	this->fileVersion = reader->ReadShort();
	this->channels = reader->ReadShort();
	this->samplesPerSecond = reader->ReadInt();
	this->bytesPerSecond = reader->ReadInt();
	this->blockAlignment= reader->ReadShort();
	this->bitsPerSample = reader->ReadShort();

	this->data = new unsigned char[this->length-20];

	for(unsigned int i = 0; i < (this->length-20); i++)
		this->data[i] = reader->ReadChar();

}

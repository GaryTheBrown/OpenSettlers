/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "WAVData.h"
Extractor::Settlers2::WAVData::WAVData(Functions::DataReader* reader) {
	this->length = reader->ReadInt();
	this->fileVersion = 0;
	this->channels = 1;
	this->samplesPerSecond = 11025;
	this->bytesPerSecond = 11025;
	this->blockAlignment= 1;
	this->bitsPerSample = 8;

	this->data = new unsigned char[this->length];

	for(unsigned int i = 0; i < (this->length); i++)
		this->data[i] = reader->ReadChar();

}

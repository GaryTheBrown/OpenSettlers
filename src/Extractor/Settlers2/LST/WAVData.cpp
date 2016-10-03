/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "WAVData.h"
Extractor::Settlers2::WAVData::WAVData(Functions::DataReader* reader)
	: Functions::WAVData(0,1,11025,11025,1,8){

	this->length = reader->ReadInt();

	this->data = new unsigned char[this->length];

	for(unsigned int i = 0; i < (this->length); i++)
		this->data[i] = reader->ReadChar();

}

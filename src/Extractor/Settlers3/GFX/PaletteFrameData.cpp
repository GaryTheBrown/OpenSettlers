/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "PaletteFrameData.h"

Extractor::Settlers3::PaletteFrameData::PaletteFrameData(Functions::DataReader* reader, unsigned int offset, RGBA* Palette) {
	reader->SetOffset(offset);
	this->sequenceCode = reader->ReadInt();
	this->sequenceHeaderSize = reader->ReadShort();
	this->sequenceUnknown06 = reader->ReadChar();
	this->count = reader->ReadChar();
	unsigned int offsets[this->count];

	for (unsigned char i = 0; i < this->count; i++){
		offsets[i] = offset + reader->ReadInt();
	}

	this->frames = new PaletteImageData*[this->count];

	for (unsigned char i = 0;i < this->count; i++){
		this->frames[i] = new PaletteImageData(reader,offsets[i],Palette);
	}
}

Extractor::Settlers3::PaletteFrameData::~PaletteFrameData() {
	for(unsigned char i = 0; i < this->count; i++){
		if(this->frames[i] != NULL){
			if (this->frames[i]->Keep() == false)
				delete this->frames[i];
		}
	}
	delete[] this->frames;
}

bool Extractor::Settlers3::PaletteFrameData::SaveToFile(std::string location){
	if(this->count > 0){
		for(unsigned char i = 0; i < this->count; i++)
			if(this->frames[i] != NULL) this->frames[i]->SaveToFile(location + "_" + Functions::ToString((int)i));
		return true;
	}
	return false;
}


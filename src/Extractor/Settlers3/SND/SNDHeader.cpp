/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "SNDHeader.h"

Extractor::Settlers3::SNDHeader::SNDHeader(Functions::DataReader* reader){
	LOGSYSTEM->Log("Reading:SND:Header...",2);
	reader->SetOffset(0);
	//Header
	this->fileID = reader->ReadInt();
	this->version = reader->ReadInt();
	this->spacer = reader->ReadInt();
	this->headerSizeA = reader->ReadInt();
	this->fileSize = reader->ReadInt();
	this->unknown20 = reader->ReadInt();
	this->headerSizeB = reader->ReadInt();

	//Data Header
	this->headerID = reader->ReadInt();
	this->unknown32 = reader->ReadShort();
	this->count = reader->ReadShort();
	unsigned int offsets[this->count];
	for (unsigned short i = 0;i < this->count;i++){
		offsets[i] = reader->ReadInt();
	}

	this->frames = new SNDFrame*[this->count];
	for (unsigned short i = 0;i < this->count;i++){
		this->frames[i] = new SNDFrame(reader,offsets[i]);
	}
}

Extractor::Settlers3::SNDHeader::~SNDHeader(){
	for (unsigned short i = 0;i < this->count;i++){
		delete this->frames[i];
	}
	delete[] this->frames;
}

void Extractor::Settlers3::SNDHeader::SaveToFile(std::string location){
	for (unsigned short i = 0;i < this->count;i++){
		if (this->frames[i] != NULL)
			this->frames[i]->SaveToFile(location + "/" + Functions::ToString(i));
	}
}

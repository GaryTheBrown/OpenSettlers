/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MAPHeader.h"

Extractor::Settlers2::MAPHeader::MAPHeader(Functions::DataReader* reader){
		this->name = reader->ReadString(20);
		unsigned short posWidth = reader->ReadShort();
		unsigned short posHeight = reader->ReadShort();
		this->gfxSet = reader->ReadChar();
		this->numPlayers = reader->ReadChar();
		this->author = reader->ReadString(20);

		for(unsigned int i = 0; i < 7; i++)
			this->playerHQx[i] = reader->ReadShort();
		for(unsigned int i = 0; i < 7; i++)
			this->playerHQy[i] = reader->ReadShort();

		this->isInvalid = reader->ReadChar();

		for(unsigned int i = 0; i < 7; i++)
			this->playerFaces[i] = reader->ReadChar();

		for(unsigned int i = 0; i < 250; i++){
			this->areaInfo[i].type = reader->ReadChar();
			this->areaInfo[i].x = reader->ReadShort();
			this->areaInfo[i].y = reader->ReadShort();
			this->areaInfo[i].size = reader->ReadInt();
		}

		 unsigned short headerSig = reader->ReadShort();

		if(headerSig == 0){ // On the map "Das Dreieck" there are 2 extra bytes here. This is a bug in the map!
			headerSig = reader->ReadShort();
			this->hasExtraWord = true;
		} else
			this->hasExtraWord = false;

		if(headerSig != 0x2711){
			LOGSYSTEM->Error("HEADER SIGNATURE INVALID");
			delete reader;
			return;
		}

		reader->ReadInt(); //UNKNOWN Might be switch for int16_t or long header blocks in WORLD#.DAT files

		this->width = reader->ReadShort();
		this->height = reader->ReadShort();

		unsigned int nameLength;
		if(this->width == posWidth && this->height == posHeight)
			nameLength = 20;
		else
			nameLength = 24;

		unsigned int tempOffset = reader->GetOffset();
		reader->SetOffset(10);
		this->name = reader->ReadString(nameLength);

		reader->SetOffset(tempOffset);

}

Extractor::Settlers2::MAPHeader::~MAPHeader() {

}

void Extractor::Settlers2::MAPHeader::SaveToFile(std::string location){
	location += "/";
}


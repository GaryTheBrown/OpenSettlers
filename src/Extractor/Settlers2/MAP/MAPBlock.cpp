/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MAPBlock.h"

Extractor::Settlers2::MAPBlock::MAPBlock(Functions::DataReader* reader){

	blockHeader.unknown = reader->ReadInt();
	blockHeader.width = reader->ReadShort();
	blockHeader.height = reader->ReadShort();
	blockHeader.multiplier = reader->ReadShort();
	blockHeader.blockLength = reader->ReadInt();

/*
	blockHeader.id = reader->ReadShort();
	if(blockHeader.id != 0x2710){
		LOGSYSTEM->Error("BLOCK HEADER ID INVALID");
		delete reader;
		return;
	}
	if(blockHeader.unknown != 0){
		LOGSYSTEM->Error("BLOCK HEADER UNKNOWN NOT ZERO");
		delete reader;
		return;
	}
	if(blockHeader.width != this->header.width){
		LOGSYSTEM->Error("BLOCK HEADER WIDTH NOT MATCHING");
		delete reader;
		return;
	}
	if(blockHeader.height != this->header.height){
		LOGSYSTEM->Error("BLOCK HEADER HEIGHT NOT MATCHING");
		delete reader;
		return;
	}
	if(blockHeader.multiplier != 1){
		LOGSYSTEM->Error("BLOCK HEADER MULTIPLIER NOT 1");
		delete reader;
		return;
	}
	if((unsigned int)blockHeader.blockLength != blockHeader.width * blockHeader.height){
		LOGSYSTEM->Error("BLOCK HEADER BLOCK LENGTH INCORRECT SIZE");
		delete reader;
		return;
	}
*/

}


Extractor::Settlers2::MAPBlock::~MAPBlock() {

}


void Extractor::Settlers2::MAPBlock::SaveToFile(std::string location){
	location += "/";
}


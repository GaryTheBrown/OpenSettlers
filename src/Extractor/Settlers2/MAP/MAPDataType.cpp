/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MAPDataType.h"

Extractor::Settlers2::MAPDataType::MAPDataType(std::string file){

	if (Functions::FileExists(file) == true){
		Functions::DataReader* reader = new Functions::DataReader(file);

		LOGSYSTEM->Log("Reading File");
		//Make Sure File Is at 0
		reader->SetOffset(0);

		std::string id = reader->ReadString(10);
		if(id != "WORLD_V1.0"){
			LOGSYSTEM->Error("HEADER ID INVALID");
			delete reader;
			return;
		}

		this->header = new MAPHeader(reader);
/*
		this->block1 = new MAPBlock(reader);
		this->block2 = new MAPBlock(reader);
		this->block3 = new MAPBlock(reader);
		this->block4 = new MAPBlock(reader);
		this->block5 = new MAPBlock(reader);
		this->block6 = new MAPBlock(reader);
		this->block7 = new MAPBlock(reader);
		this->block8 = new MAPBlock(reader);
		this->block9 = new MAPBlock(reader);
		this->block10 = new MAPBlock(reader);
		this->block11 = new MAPBlock(reader);
		this->block12 = new MAPBlock(reader);
		this->block13 = new MAPBlock(reader);
		this->block14 = new MAPBlock(reader);
		this->footer = new MAPBlock(reader);
*/
		LOGSYSTEM->Log("EXTRACT COMPLETED");

	}
}

Extractor::Settlers2::MAPDataType::~MAPDataType() {
	delete this->header;
/*
	delete this->block1;
	delete this->block2;
	delete this->block3;
	delete this->block4;
	delete this->block5;
	delete this->block6;
	delete this->block7;
	delete this->block8;
	delete this->block9;
	delete this->block10;
	delete this->block11;
	delete this->block12;
	delete this->block13;
	delete this->block14;
	delete this->footer;
*/
}


void Extractor::Settlers2::MAPDataType::SaveToFile(std::string location){
	location += "/";
	LOGSYSTEM->Log("TODO IMPLEMETE SAVE");
}


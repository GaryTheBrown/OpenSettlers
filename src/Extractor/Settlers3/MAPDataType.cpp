/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MAPDataType.h"

Extractor::Settlers3::MAPDataType::MAPDataType(std::string file){
	LOGSYSTEM->Log("File:" + file,2);
	Functions::DataReader* reader = new Functions::DataReader(file);
	reader->SetOffset(0);
	LOGSYSTEM->Log("Reading Header.",2);
	this->header = new MAPHeader(reader);
	LOGSYSTEM->Log("Finished Reading Data To Memory.",2);
}

Extractor::Settlers3::MAPDataType::~MAPDataType(){
	if(this->header != NULL){
		LOGSYSTEM->Log("Deleting Header...",2);
		delete this->header;
	}
	LOGSYSTEM->Log("Finished Deleting.",2);
}

void Extractor::Settlers3::MAPDataType::SaveHeaderData(std::string location){

	std::string data;
	if(this->header != NULL){
		data += "**HEADER**\n";
		data += this->header->HeaderToString();
	}
	Functions::SaveToTextFile(location + "/Header.txt",data);
}

void Extractor::Settlers3::MAPDataType::SaveToFile(std::string location){
	if(this->header != NULL){
		LOGSYSTEM->Log("Saving Map Data",2);
		this->header->SaveToFile(location);
	}
}

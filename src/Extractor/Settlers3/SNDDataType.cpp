/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "../Settlers3/SNDDataType.h"

Extractor::Settlers3::SNDDataType::SNDDataType(std::string file){

	if (Functions::FileExists(file) == true){
		Functions::DataReader* reader = new Functions::DataReader(file);
		unsigned int headCode = reader->ReadInt();

		//Make sure file is for Settlers 3
		if (headCode != 0x011544){
			LOGSYSTEM->Error(file + "is not a Settlers 3 SND File.");
		}else{
			this->header = new SNDHeader(reader);
			LOGSYSTEM->Log("Finished Reading Data To Memory.",2);
		}
		if (reader != NULL) delete reader;
	}
}

Extractor::Settlers3::SNDDataType::~SNDDataType(){
	if(this->header != NULL){
		LOGSYSTEM->Log("Clean up Data...",2);
		delete this->header;
	}
	LOGSYSTEM->Log("Finished Clean up.",2);
}

void Extractor::Settlers3::SNDDataType::SaveToFile(std::string location){
	if(this->header != NULL){
		LOGSYSTEM->Log("Saving Sound Data...",2);
		this->header->SaveToFile(location);
	}
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MapSettlers.h"

Extractor::Settlers3::MAPSettlers::MAPSettlers(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey):MAPParts(reader,offset,size,cryptKey,false){

	if(this->hasBeenDecrypted){

		if (this->size == 0){
			LOGSYSTEM->Error("No area-information available in mapfile!");
			return;
		}
		//- height and width are the same
		this->settlerCount = reader->ReadInt();

		this->settlers = new Settler[this->settlerCount];

		for (unsigned int i = 0; i < this->settlerCount; i++){
			this->settlers[i].player = reader->ReadChar();
			this->settlers[i].type = reader->ReadChar();
			this->settlers[i].x_pos = reader->ReadShort();
			this->settlers[i].y_pos = reader->ReadShort();
		}
	}
	else{
		//decryption failed
		LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
	}
}

std::string Extractor::Settlers3::MAPSettlers::HeaderToString(){

	if (this->hasBeenDecrypted == false)
		return MAPParts::HeaderToString();

	std::string returnString;
	returnString += "SETTLERCOUNT=" + Functions::ToString(this->settlerCount) + "\n";

	for (unsigned int i = 0; i < this->settlerCount; i++){
		returnString += "Settler:" + Functions::ToString(i+1) + "\n";
		returnString += "\tPlayer=" + Functions::ToString((int)this->settlers[i].player) + "\n";
		returnString += "\tType=" + SettlersList[(int)this->settlers[i].type] + "\n";
		returnString += "\tX Pos=" + Functions::ToString((int)this->settlers[i].x_pos) + "\n";
		returnString += "\tY Pos=" + Functions::ToString((int)this->settlers[i].y_pos) + "\n";
	}
	return returnString;
}

void Extractor::Settlers3::MAPSettlers::SaveToFile(std::string location){

	Functions::SaveToTextFile(location + "/Settlers.txt",this->HeaderToString());
}

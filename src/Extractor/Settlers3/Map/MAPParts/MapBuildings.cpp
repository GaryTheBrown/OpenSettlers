/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MapBuildings.h"

Extractor::Settlers3::MAPBuildings::MAPBuildings(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey):MAPParts(reader,offset,size,cryptKey,false){

	if(this->hasBeenDecrypted){

		if (this->size == 0){
			LOGSYSTEM->Error("No area-information available in mapfile!");
			return;
		}
		//- height and width are the same
		this->buildingCount = reader->ReadInt();

		this->buildings = new Building[this->buildingCount];

		for (unsigned int i = 0; i < this->buildingCount; i++){
			this->buildings[i].player = reader->ReadChar();
			this->buildings[i].type = reader->ReadChar();
			this->buildings[i].x_pos = reader->ReadShort();
			this->buildings[i].y_pos = reader->ReadShort();

			//if Military Building
			if ((this->buildings[i].type == 15)||(this->buildings[i].type == 16)||(this->buildings[i].type == 18)){
				this->buildings[i].soldiers.unknown = reader->ReadChar();
				char tmp = reader->ReadChar();
				this->buildings[i].soldiers.sword1 = tmp >> 4;
				this->buildings[i].soldiers.sword2 = tmp & 0xf;
				tmp = reader->ReadChar();
				this->buildings[i].soldiers.bow2 = tmp >> 4;
				this->buildings[i].soldiers.bow3 = tmp & 0xf;
				tmp = reader->ReadChar();
				this->buildings[i].soldiers.sword3 = tmp >> 4;
				this->buildings[i].soldiers.bow1 = tmp & 0xf;
				tmp = reader->ReadChar();
				this->buildings[i].soldiers.spear3 = tmp >> 4;
				tmp = reader->ReadChar();
				this->buildings[i].soldiers.spear1 = tmp >> 4;
				this->buildings[i].soldiers.spear2 = tmp & 0xf;
			}
			else{
				reader->ReadInt();
				reader->ReadShort();
			}
		}
	}
	else{
		//decryption failed
		LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
	}
}

std::string Extractor::Settlers3::MAPBuildings::HeaderToString(){

	if (this->hasBeenDecrypted == false)
		return MAPParts::HeaderToString();

	std::string returnString;
	returnString += "BUILDINGCOUNT=" + Functions::ToString(this->buildingCount) + "\n";

	for (unsigned int i = 0; i < this->buildingCount; i++){
		returnString += "BUILDING:" + Functions::ToString(i+1) + "\n";
		returnString += "\tPlayer=" + Functions::ToString((int)this->buildings[i].player) + "\n";
		returnString += "\tType=" + BuildingsList[(int)this->buildings[i].type] + "\n";
		returnString += "\tX Pos=" + Functions::ToString((int)this->buildings[i].x_pos) + "\n";
		returnString += "\tY Pos=" + Functions::ToString((int)this->buildings[i].y_pos) + "\n";

		if ((this->buildings[i].type == 15)||(this->buildings[i].type == 16)||(this->buildings[i].type == 18)){
			returnString += "\tUnknown=" + Functions::ToString((int)this->buildings[i].soldiers.unknown) + "\n";
			returnString += "\tSword Level 1=" + Functions::ToString((int)this->buildings[i].soldiers.sword1) + "\n";
			returnString += "\tSword Level 2=" + Functions::ToString((int)this->buildings[i].soldiers.sword2) + "\n";
			returnString += "\tSword Level 3=" + Functions::ToString((int)this->buildings[i].soldiers.sword3) + "\n";
			returnString += "\tBow Level 1=" + Functions::ToString((int)this->buildings[i].soldiers.bow1) + "\n";
			returnString += "\tBow Level 2=" + Functions::ToString((int)this->buildings[i].soldiers.bow2) + "\n";
			returnString += "\tBow Level 3=" + Functions::ToString((int)this->buildings[i].soldiers.bow3) + "\n";
			returnString += "\tSpear Level 1=" + Functions::ToString((int)this->buildings[i].soldiers.spear1) + "\n";
			returnString += "\tSpear Level 2=" + Functions::ToString((int)this->buildings[i].soldiers.spear2) + "\n";
			returnString += "\tSpear Level 3=" + Functions::ToString((int)this->buildings[i].soldiers.spear3) + "\n";
		}
	}
	return returnString;
}

void Extractor::Settlers3::MAPBuildings::SaveFileData(std::string location){

	Functions::SaveToTextFile(location + "/Buildings.txt",this->HeaderToString());
}

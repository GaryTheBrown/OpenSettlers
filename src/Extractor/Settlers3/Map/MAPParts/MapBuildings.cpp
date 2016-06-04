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

namespace Extractor{
	namespace Settlers3{
		MAPBuildings::MAPBuildings(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey):MAPParts(reader,offset,size,cryptKey,false){

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
					this->buildings[i].unknown1 = reader->ReadChar();
					this->buildings[i].unknown2 = reader->ReadChar();
					this->buildings[i].unknown3 = reader->ReadChar();
					this->buildings[i].unknown4 = reader->ReadChar();
					this->buildings[i].unknown5 = reader->ReadChar();
					this->buildings[i].unknown6 = reader->ReadChar();
				}
			}
			else{
				//decryption failed
				LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
			}
		}

		MAPBuildings::~MAPBuildings(){
			delete [] this->buildings;
		}

		std::string MAPBuildings::HeaderToString(){

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
				returnString += "\t" + Functions::OutputVar("Unknown 1",(int)this->buildings[i].unknown1) + "\n";
				returnString += "\t" + Functions::OutputVar("Unknown 2",(int)this->buildings[i].unknown2) + "\n";
				returnString += "\t" + Functions::OutputVar("Unknown 3",(int)this->buildings[i].unknown3) + "\n";
				returnString += "\t" + Functions::OutputVar("Unknown 4",(int)this->buildings[i].unknown4) + "\n";
				returnString += "\t" + Functions::OutputVar("Unknown 5",(int)this->buildings[i].unknown5) + "\n";
				returnString += "\t" + Functions::OutputVar("Unknown 6",(int)this->buildings[i].unknown6) + "\n";
				/*
				returnString += "\tUnknown1=" + Functions::ToString((int)this->buildings[i].unknown1) + "\n";
				returnString += "\tUnknown2=" + Functions::ToString((int)this->buildings[i].unknown2) + "\n";
				returnString += "\tUnknown3=" + Functions::ToString((int)this->buildings[i].unknown3) + "\n";
				returnString += "\tUnknown4=" + Functions::ToString((int)this->buildings[i].unknown4) + "\n";
				returnString += "\tUnknown5=" + Functions::ToString((int)this->buildings[i].unknown5) + "\n";
				returnString += "\tUnknown6=" + Functions::ToString((int)this->buildings[i].unknown6) + "\n";
				*/
			}
			return returnString;
		}

		void MAPBuildings::SaveFileData(std::string location){

			Functions::SaveToTextFile(location + "/Buildings.txt",this->HeaderToString());
		}
	}
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MapInfo.h"

namespace Extractor{
	namespace Settlers3{
		MAPInfo::MAPInfo(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey):MAPParts(reader,offset,size,cryptKey,false) {

			if(this->hasBeenDecrypted){

				if (this->size == 0){
					LOGSYSTEM->Error("No information available in Map File!");
					return;
				}

				//- single or Multiplayer map?

				signed int tmpVal = reader->ReadInt();
				if (tmpVal <= 1){
					this->isSinglePlayerMap = (tmpVal == 1);
				}
				else{
				LOGSYSTEM->Error("wrong value for isSinglePlayerMap value: " + Functions::ToString(tmpVal));
				}

				this->playerCount = reader->ReadInt();
				if ((this->playerCount<1) || (this->playerCount>20)){
					LOGSYSTEM->Error("wrong value for PlayerCount value: " + this->playerCount);
					this->playerCount = 20;
				}

				this->startResources = (enumStartResources)reader->ReadInt();

				if ((this->startResources != enumStartResources::startResourceLow) && (this->startResources != enumStartResources::startResourcesNormal) && (this->startResources != enumStartResources::startResourcesHigh)){
					LOGSYSTEM->Error("wrong value for StartResources value: " + this->startResources);
					this->startResources = enumStartResources::startResourceLow;
				}
			}
			else{
				//decryption failed
				LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
			}
		}

		MAPInfo::~MAPInfo() {

		}

		std::string MAPInfo::ToString(){
			if (this->hasBeenDecrypted == false)
				return MAPParts::HeaderToString();

			std::string returnString;
			returnString += "SinglePlayerMap=";
					if (this->isSinglePlayerMap)
						returnString += "true\n";
					else
						returnString += "false\n";
			returnString += "PlayerCount=" + Functions::ToString(this->playerCount) + "\n";
			returnString += "StartingResource=";
			switch(this->startResources){
			case startResourceLow:
				returnString += "Low\n";
				break;
			case startResourcesNormal:
				returnString += "Normal\n";
				break;
			case startResourcesHigh:
				returnString += "High\n";
				break;
			default:
				returnString += "UNKNOWN\n";
			}
			return returnString;

		}
	}
}

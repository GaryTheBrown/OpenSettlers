/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MapArea.h"

namespace Extractor{
	namespace Settlers3{
		MAPArea::MAPArea(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey):MAPParts(reader,offset,size,cryptKey,false){

			if(this->hasBeenDecrypted){

				if (this->size == 0){
					LOGSYSTEM->Error("No area-information available in mapfile!");
					return;
				}
				//- height and width are the same
				this->mapSizeHeight = this->mapSizeWidth = reader->ReadInt();

				unsigned int dataCount = this->mapSizeHeight * this->mapSizeWidth;

				this->mapData = new MapTile[dataCount];

				for (unsigned int i = 0; i < dataCount; i++){
					this->mapData[i].height = reader->ReadChar();
					this->mapData[i].type = reader->ReadChar();
					this->mapData[i].object = reader->ReadChar();
					this->mapData[i].playerClaim = reader->ReadChar();
					this->mapData[i].accessible = reader->ReadChar();
					this->mapData[i].resources = reader->ReadChar();
				}
			}
			else{
				//decryption failed
				LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
			}
		}

		MAPArea::~MAPArea(){
			delete [] this->mapData;
		}

		std::string MAPArea::HeaderToString(){

			if (this->hasBeenDecrypted == false)
				return MAPParts::HeaderToString();

			std::string returnString;

			returnString += "MapSizeWidth=" + Functions::ToString(this->mapSizeWidth) + "\n";
			returnString += "MapSizeHeight=" + Functions::ToString(this->mapSizeHeight) + "\n";

			return returnString;
		}

		void MAPArea::SaveFileData(std::string location){

			unsigned int dataSize = this->mapSizeHeight*this->mapSizeWidth;
			char* Aheight = new char[dataSize];
			char* Atype = new char[dataSize];
			char* Aobject = new char[dataSize];
			char* AplayerClaim = new char[dataSize];
			char* Aaccessible = new char[dataSize];
			char* Aresources = new char[dataSize];

			for(unsigned int i = 0; i < (dataSize); i++){
				Aheight[i] = this->mapData[i].height;
				Atype[i] = this->mapData[i].type;
				Aobject[i] = this->mapData[i].object;
				AplayerClaim[i] = this->mapData[i].playerClaim;
				Aaccessible[i] = this->mapData[i].accessible;
				Aresources[i] = this->mapData[i].resources;
			}

			Functions::SaveToBinaryFile(location + "/Height.RAW",Aheight,dataSize);
			Functions::SaveToBinaryFile(location + "/Type.RAW",Atype,dataSize);
			Functions::SaveToBinaryFile(location + "/Object.RAW",Aobject,dataSize);
			Functions::SaveToBinaryFile(location + "/PlayerClaim.RAW",AplayerClaim,dataSize);
			Functions::SaveToBinaryFile(location +"/Accessible.RAW",Aaccessible,dataSize);
			Functions::SaveToBinaryFile(location + "/Resources.RAW",Aresources,dataSize);

			std::string heightText,typeText,objectText,playerClaimText,accessibleText,resourcesText;

			for(unsigned int i = 0; i < dataSize;i++){
				if((i != 0)&&(i % this->mapSizeWidth == 0)){
					heightText += "\n";
					typeText += "\n";
					objectText += "\n";
					playerClaimText += "\n";
					accessibleText += "\n";
					resourcesText += "\n";
				}
				heightText += Functions::ToString((int)this->mapData[i].height) + ",";
				typeText += Functions::ToString((int)this->mapData[i].type) + ",";
				objectText += MapObjectsList[this->mapData[i].object] + ",";
				playerClaimText += Functions::ToString((int)this->mapData[i].playerClaim) + ",";
				accessibleText += Functions::ToString((int)this->mapData[i].accessible) + ",";
				resourcesText += ResourcesList[this->mapData[i].resources] + ",";
			}
			Functions::SaveToTextFile(location + "/MapArea_Height.txt",heightText);
			Functions::SaveToTextFile(location + "/MapArea_Type.txt",typeText);
			Functions::SaveToTextFile(location + "/MapArea_Object.txt",objectText);
			Functions::SaveToTextFile(location + "/MapArea_PlayerClaim.txt",playerClaimText);
			Functions::SaveToTextFile(location + "/MapArea_Accessible.txt",accessibleText);
			Functions::SaveToTextFile(location + "/MapArea_Resources.txt",resourcesText);
		}
	}
}

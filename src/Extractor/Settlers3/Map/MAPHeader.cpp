/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MAPHeader.h"

Extractor::Settlers3::MAPHeader::MAPHeader(Functions::DataReader* reader){
	reader->SetOffset(0);
	this->fileChecksum = reader->ReadInt();
	this->fileVersion = (enumFileVersion)reader->ReadInt();

	this->goodChecksum = this->CheckChecksum(reader);
	if (this->goodChecksum == false){
		LOGSYSTEM->Error("Wrong checksum of map-file" + reader->FileName());
		return;
	}


	if ((this->fileVersion != enumFileVersion::FILE_VERSION_DEFAULT) && (this->fileVersion != enumFileVersion::FILE_VERSION_AMAZONS)){
		this->fileVersion = enumFileVersion::FILE_VERSION_NONE;
		LOGSYSTEM->Error("Wrong map-file version " + this->fileVersion);
		return;
	}

	unsigned int mapPartType = 0;
	unsigned int mapPartLen = 0;
	unsigned int filePos = 8; //- start of map-content

	do{
		reader->SetOffset(filePos);
		mapPartType = reader->ReadInt() & 0xFFFF;
		mapPartLen = reader->ReadInt() - 8;

		int mapPartPos = reader->GetOffset();
		//- next pos in File
		filePos = filePos + mapPartLen + 8;

		switch((enumFileParts)mapPartType){
		case PART_TYPE_MapInfo:
			this->mapInfo = new MAPInfo(reader,mapPartPos,mapPartLen,mapPartType);
			break;
		case PART_TYPE_PreviewImage:
			this->preview = new MAPPreviewImage(reader,mapPartPos,mapPartLen,mapPartType);
			break;
		case PART_TYPE_Area:
			this->area = new MAPArea(reader,mapPartPos,mapPartLen,mapPartType);
			break;
		case PART_TYPE_PlayerInfo:
			this->playerInfo = new MAPPlayerInfo(reader,mapPartPos,mapPartLen,mapPartType,this->mapInfo->PlayerCount());
			break;
		case PART_TYPE_TeamInfo:
			this->teamInfo = new MAPTeamInfo(reader,mapPartPos,mapPartLen,mapPartType,this->mapInfo->PlayerCount());
			break;
		case PART_TYPE_Settlers:
			this->settlers = new MAPSettlers(reader,mapPartPos,mapPartLen,mapPartType);
			break;
		case PART_TYPE_Buildings:
			this->buildings = new MAPBuildings(reader,mapPartPos,mapPartLen,mapPartType);
			break;
		case PART_TYPE_Resources:
			this->goods = new MAPGoods(reader,mapPartPos,mapPartLen,mapPartType);
			break;
		case PART_TYPE_VictoryConditions:
			this->victoryConditions = new MAPVictoryConditions(reader,mapPartPos,mapPartLen,mapPartType);
			break;
		case PART_TYPE_QuestText:
			this->questText = new MAPText(reader,mapPartPos,mapPartLen,mapPartType);
			break;
		case PART_TYPE_QuestTip:
			this->questTip = new MAPText(reader,mapPartPos,mapPartLen,mapPartType);
			break;
		default:
			//If none of the above ignore it and move on
			break;
		}
	}
	while (((enumFileParts)mapPartType != PART_TYPE_EOF) && (reader->EndOfFile() == false));
}

Extractor::Settlers3::MAPHeader::~MAPHeader(){
	if (this->mapInfo != NULL)
		delete this->mapInfo;
	if (this->area != NULL)
		delete this->area;
	if (this->preview != NULL)
		delete this->preview;
	if (this->playerInfo != NULL)
		delete this->playerInfo;
	if (this->teamInfo != NULL)
		delete this->teamInfo;
	if (this->settlers != NULL)
		delete this->settlers;
	if (this->buildings != NULL)
		delete this->buildings;
	if (this->goods != NULL)
		delete this->goods;
	if (this->victoryConditions != NULL)
		delete this->victoryConditions;
	if (this->questText != NULL)
		delete this->questText;
	if (this->questTip != NULL)
		delete this->questTip;
}

std::string Extractor::Settlers3::MAPHeader::HeaderToString(){
	std::string returnString;
	returnString += "##HEADER INFO##\n";
	returnString += "CheckSum=" + Functions::ToString(this->fileChecksum) + "\n";
	returnString += "FileVersion=";
	switch(this->fileVersion){
	case FILE_VERSION_NONE:
		returnString += "None\n";
		break;
	case FILE_VERSION_DEFAULT:
		returnString += "Default(S3)(No Amazon)\n";
		break;
	case FILE_VERSION_AMAZONS:
		returnString += "Amazon\n";
		break;
	default:
		returnString += "UNKNOWN\n";
	}
	returnString += "\n";//LineSpace
	if(this->mapInfo != NULL){
		returnString += "##MAP INFO##\n";
		returnString += this->mapInfo->ToString();
		returnString += "\n";//LineSpace
	}
	if (this->playerInfo != NULL){
		returnString += "##PLAYER INFO##\n";
		returnString += this->playerInfo->ToString();
		returnString += "\n";//LineSpace
	}
	if (this->teamInfo != NULL){
		returnString += "##TEAM INFO##\n";
		returnString += this->teamInfo->ToString();
		returnString += "\n";//LineSpace
	}
	if(this->area != NULL){
		returnString += "##MAP AREA##\n";
		returnString += this->area->HeaderToString();
		returnString += "\n";//LineSpace
	}
	if (this->victoryConditions != NULL){
		returnString += "##VICTORY CONDITIONS INFO##\n";
		returnString += this->victoryConditions->ToString();
		returnString += "\n";//LineSpace
	}

	if ((this->questText != NULL)&&(this->questTip != NULL)){
		returnString += "##Quest Text##\n";
	}

	if (this->questText != NULL){
		returnString += "Quest Description ";
		returnString += this->questText->ToString();
	}
	if (this->questTip != NULL){
		returnString += "Quest Tip ";
		returnString += this->questTip->ToString();
	}
	return returnString;
}

void Extractor::Settlers3::MAPHeader::SaveToFile(std::string location){

	if(this->area != NULL)
		this->area->SaveFileData(location);

	if(this->preview != NULL)
		this->preview->SaveFileData(location);

	if (this->settlers != NULL)
		this->settlers->SaveFileData(location);

	if (this->buildings != NULL)
		this->buildings->SaveFileData(location);

	if (this->goods != NULL)
		this->goods->SaveFileData(location);

}

bool Extractor::Settlers3::MAPHeader::CheckChecksum(Functions::DataReader * reader){
	//- get Length of file in Integers then remove 2 for header
	const unsigned int count = (reader->FileSize()/4) - 2;

	//- Move reader to Start position.
	reader->SetOffset(8);

	unsigned int checksum = 0;

	for (unsigned int i = 0; i < count; i++){
		unsigned int currentDWord = reader->ReadInt();
		checksum = ((checksum >> 31) | ((checksum << 1) ^ currentDWord));
	}
	if (checksum != this->fileChecksum)
		return false;
	return true;
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GameType.h"

OSData::GameType::GameType():FileTypes(eFull){
	this->menuLayouts = new std::vector<MenuLayout*>();
	this->loadingScreenLayouts = new std::vector<LoadingScreenLayout*>();
}

OSData::GameType::GameType(std::string gameName, unsigned char gameNumber, GameAddons addonsIncluded, unsigned int startMenuNumber):
		FileTypes(eFull),
		gameName(gameName),
		gameNumber(gameNumber),
		addonsIncluded(addonsIncluded),
		startMenuNumber(startMenuNumber){

	this->menuLayouts = new std::vector<MenuLayout*>();
	this->loadingScreenLayouts = new std::vector<LoadingScreenLayout*>();
}

OSData::GameType::GameType(std::string gameName, unsigned char gameNumber, GameAddons addonsIncluded, unsigned int startMenuNumber, std::vector<MenuLayout*>* menuLayouts, std::vector<LoadingScreenLayout*>* loadingScreenLayouts
//		GameOptions* gameOptions,
//		Layout* layout,
//		MapSetup* mapSetup,
//		List<Resource>* resourceList,
//		List<Race>* raceList
		):
		FileTypes(eFull),
		gameName(gameName),
		gameNumber(gameNumber),
		addonsIncluded(addonsIncluded),
		startMenuNumber(startMenuNumber),
		menuLayouts(menuLayouts),
		loadingScreenLayouts(loadingScreenLayouts){

	std::sort(this->menuLayouts->begin(),this->menuLayouts->end());
	std::sort(this->loadingScreenLayouts->begin(),this->loadingScreenLayouts->end());

//	this->gameOptions = gameOptions;
//	this->layout = layout;
//	this->mapSetup = mapSetup;
//	this->resourceList = resourceList;
//	this->raceList = raceList;

}

OSData::GameType::GameType(Functions::DataReader* reader)
	:FileTypes(eFull){

	unsigned int textSize = reader->ReadChar();
	this->gameName = reader->ReadString(textSize);
	this->gameNumber = reader->ReadChar();
	this->addonsIncluded = static_cast<GameAddons>(reader->ReadChar());
	this->startMenuNumber = reader->ReadInt();

	unsigned int itemCount = reader->ReadInt();
		for (unsigned int i = 0; i < itemCount; i++){
		OSData::FileTypes::eFileType fileType = static_cast<FileTypes::eFileType>(reader->ReadShort());
		this->DoFileType(fileType, reader);
	}
}

OSData::GameType::GameType(xmlNode* node):FileTypes(eFull){
	if(node != NULL){
		xmlAttr* xmlAttribute = node->properties;
		while(xmlAttribute){
			this->CheckValues(((char*)xmlAttribute->name),((char*)xmlAttribute->children->content));
			xmlAttribute = xmlAttribute->next;
		}

//		xmlNode* itemNode = node->children;
//		while(itemNode){
//			this->CheckValues(((char*)itemNode->name),((char*)itemNode->content));
//			itemNode = itemNode->next;
//		}

		xmlNode* itemNode = node->children;
		while(itemNode){
			FileTypes::eFileType fileType = GetFileType((char*)itemNode->name);
			if (fileType != FileTypes::eNone)
				this->DoFileType(fileType, itemNode,true);
			itemNode = itemNode->next;
		}
	}
}

OSData::GameType::~GameType() {

	if(this->menuLayouts != NULL){
		for(auto item=this->menuLayouts->begin() ; item < this->menuLayouts->end(); item++ ){
			delete (*item);
		}
		this->menuLayouts->clear();
		delete this->menuLayouts;
	}
	if(this->loadingScreenLayouts != NULL){
		for(auto item=this->loadingScreenLayouts->begin() ; item < this->loadingScreenLayouts->end(); item++ ){
			delete (*item);
		}
		this->loadingScreenLayouts->clear();
		delete this->loadingScreenLayouts;
	}
//	if(this->gameOptions != NULL){
//	if(this->layout != NULL){
//	if(this->raceList != NULL){
//	if(this->resourceList != NULL){
//	if(this->mapSetup != NULL){
}

void OSData::GameType::CheckValues(std::string name, std::string value){
	if (name == "Name")
		this->gameName = value;
	if (name == "StartMenu")
		this->startMenuNumber = atoi(value.c_str());
	if (name == "gameNumber")
		this->gameName = atoi(value.c_str());
}

OSData::FileTypes::eFileType OSData::GameType::GetFileType(std::string data){
	if (data == "MenuLayout")
		return FileTypes::eMenuLayout;
	else if (data == "LoadScreen")
		return FileTypes::eLoadingScreenLayout;
	else //Includes Full and Archive
		return FileTypes::eNone;
}

void OSData::GameType::DoFileType(FileTypes::eFileType fileType, void* data, bool xml){

	switch(fileType){

	case FileTypes::eMenuLayout:
		if(this->menuLayouts == NULL)
			this->menuLayouts = new std::vector<MenuLayout*>();
		if(xml)
			this->menuLayouts->push_back(new MenuLayout((xmlNode*)data));
		else
			this->menuLayouts->push_back(new MenuLayout((Functions::DataReader*)data));
		break;
	case FileTypes::eLoadingScreenLayout:
		if(this->loadingScreenLayouts == NULL)
			this->loadingScreenLayouts = new std::vector<LoadingScreenLayout*>();
		if(xml)
			this->loadingScreenLayouts->push_back(new LoadingScreenLayout((xmlNode*)data));
		else
			this->loadingScreenLayouts->push_back(new LoadingScreenLayout((Functions::DataReader*)data));
		break;

	//Ignore these
	case FileTypes::eFull:
	case FileTypes::eArchive:
	default:
		break;
	}
}

void OSData::GameType::AddMenuLayout(OSData::MenuLayout* menuLayout){
	if(this->menuLayouts == NULL)
		this->menuLayouts = new std::vector<MenuLayout*>();
	//First Check the Image is not already Loaded
	for(auto ml = this->menuLayouts->begin() ; ml < this->menuLayouts->end(); ml++ ){
		if (menuLayout->MenuID() == (*ml)->MenuID()){
			LOGSYSTEM->Error("MENU LAYOUT ALREADY IN FILE");
			return;
		}
	}
	this->menuLayouts->push_back(menuLayout);
}

void OSData::GameType::AddLoadingScreenLayout(OSData::LoadingScreenLayout* loadingScreenLayout){
	if(this->loadingScreenLayouts == NULL)
		this->loadingScreenLayouts = new std::vector<LoadingScreenLayout*>();
	//First Check the Image is not already Loaded
	for(auto ml = this->loadingScreenLayouts->begin() ; ml < this->loadingScreenLayouts->end(); ml++ ){
		if (loadingScreenLayout->MenuID() == (*ml)->MenuID()){
			LOGSYSTEM->Error("LOADING SCREEN LAYOUT ALREADY IN FILE");
			return;
		}
	}
	this->loadingScreenLayouts->push_back(loadingScreenLayout);
}

void OSData::GameType::SortAll(){
	//TODO FIX THIS FUNCTION
	std::sort(this->menuLayouts->begin(),this->menuLayouts->end());
}

bool OSData::GameType::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;

	FileTypes::ToSaveToData(data);

	//text Size (char)
	data->push_back(static_cast<char>(this->gameName.size()));
	//Text
	std::copy(this->gameName.begin(), this->gameName.end(), std::back_inserter(*data));

	//Game Number (char)
	data->push_back(this->gameNumber);

	//Game Addons (GameAddons)(char)
	data->push_back(static_cast<char>(this->addonsIncluded));
	//Start Menu Number (int)
	data->push_back(this->startMenuNumber & 0xFF);
	data->push_back((this->startMenuNumber >> 8) & 0xFF);
	data->push_back((this->startMenuNumber >> 16) & 0xFF);
	data->push_back((this->startMenuNumber >> 24) & 0xFF);

	//Data Count (Short)
	unsigned int count = 0; //+ all others added on when added
	if (this->menuLayouts != NULL)
		count += this->menuLayouts->size();
	if (this->loadingScreenLayouts != NULL)
		count += this->loadingScreenLayouts->size();

	data->push_back(count & 0xFF);
	data->push_back((count >> 8) & 0xFF);
	data->push_back((count >> 16) & 0xFF);
	data->push_back((count >> 24) & 0xFF);

	//MenuLayout Data
	if (this->menuLayouts != NULL){
		for(auto menuLayout = this->menuLayouts->begin(); menuLayout < this->menuLayouts->end(); menuLayout++) {
			if((*menuLayout)->ToSaveToData(data) == false) return false;
		}
	}

	//loadingScreenLayout Data
	if (this->loadingScreenLayouts != NULL){
		for(auto loadingScreenLayout = this->loadingScreenLayouts->begin(); loadingScreenLayout < this->loadingScreenLayouts->end(); loadingScreenLayout++) {
			if((*loadingScreenLayout)->ToSaveToData(data) == false) return false;
		}
	}

	return true;
}

bool OSData::GameType::ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations){
	if (images == NULL) return false;
	if (this->menuLayouts != NULL){
		for(auto item = this->menuLayouts->begin(); item < this->menuLayouts->end(); item++) {
			if((*item)->ImageToNumbers(images,imageLocations) == false) return false;
		}
	}
	if (this->loadingScreenLayouts != NULL){
		for(auto item = this->loadingScreenLayouts->begin(); item < this->loadingScreenLayouts->end(); item++) {
			if((*item)->ImageToNumbers(images,imageLocations) == false) return false;
		}
	}
	return true;
}

bool OSData::GameType::LinkNumbers(std::vector<Functions::RGBImage*>* images){
	if (images == NULL) return false;
	if (this->menuLayouts != NULL){
		for(auto item = this->menuLayouts->begin(); item != this->menuLayouts->end(); item++) {
			if((*item)->LinkNumbers(images) == false) return false;
		}
	}
	if (this->loadingScreenLayouts != NULL){
		for(auto item = this->loadingScreenLayouts->begin(); item != this->loadingScreenLayouts->end(); item++) {
			if((*item)->LinkNumbers(images) == false) return false;
		}
	}

	return true;
}


std::string OSData::GameType::ToString(){

	std::string data;

	data += "GameName=" + this->gameName + "\n";
	data += "GameNumber=" + Functions::ToString((int)this->gameNumber) + "\n";
	data += "AddonsIncluded=";
	switch(this->gameNumber){
	case 2:
		data += ((this->addonsIncluded & OSData::eS2MissionCD)?"S2MCD ":"");
		data += ((this->addonsIncluded & OSData::eS2Gold)?"S2GOLD ":"");
		break;
	case 3:
		data += ((this->addonsIncluded & OSData::eS3MissionCD)?"S3MCD ":"");
		data += ((this->addonsIncluded & OSData::eS3Amazon)?"S3AMAZON ":"");
		data += ((this->addonsIncluded & OSData::eS3Gold)?"S3GOLD ":"");
		break;
	case 4:
		data += ((this->addonsIncluded & OSData::eS4MissionCD)?"S4MCD ":"");
		data += ((this->addonsIncluded & OSData::eS4Trojan)?"S4TROJAN ":"");
		data += ((this->addonsIncluded & OSData::eS4Gold)?"S4GOLD ":"");
		data += ((this->addonsIncluded & OSData::eS4NewWorld)?"S4NEWWORLD ":"");
		data += ((this->addonsIncluded & OSData::eS4Community)?"S4COMMUNITY ":"");
		break;
	default:
		break;
	}
	data +=  "\n";

	if(this->menuLayouts != NULL){
		for(auto item=this->menuLayouts->begin() ; item < this->menuLayouts->end(); item++ ){
			data += (*item)->ToString();
		}
	}

	return data;
}

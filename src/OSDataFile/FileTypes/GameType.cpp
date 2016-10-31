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
}

OSData::GameType::GameType(std::string gameName, unsigned int startMenuNumber):
		FileTypes(eFull),
		gameName(gameName),
		startMenuNumber(startMenuNumber){

	this->menuLayouts = new std::vector<MenuLayout*>();
}

OSData::GameType::GameType(std::string gameName, unsigned int startMenuNumber, std::vector<MenuLayout*>* menuLayouts
//		GameOptions* gameOptions,
//		Layout* layout,
//		MapSetup* mapSetup,
//		List<Resource>* resourceList,
//		List<Race>* raceList
		):
		FileTypes(eFull),
		gameName(gameName),
		startMenuNumber(startMenuNumber),
		menuLayouts(menuLayouts){

	std::sort(this->menuLayouts->begin(),this->menuLayouts->end());

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
			FileTypes::eFileType fileType = GetFileType((char*)node->children->name);
			this->DoFileType(fileType, node->children,true);
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
}

OSData::FileTypes::eFileType OSData::GameType::GetFileType(std::string data){
	if (data == "MenuLayout")
		return FileTypes::eMenuLayout;
	else if (data == "LoadScreen")
		return FileTypes::eLoadScreen;
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
	case FileTypes::eLoadScreen:
		break;

	//Ignore these
	case FileTypes::eFull:
	case FileTypes::eArchive:
	default:
		break;
	}
}

bool OSData::GameType::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;

	FileTypes::ToSaveToData(data);

	//text Size (char)
	data->push_back(static_cast<char>(this->gameName.size()));
	//Text
	std::copy(this->gameName.begin(), this->gameName.end(), std::back_inserter(*data));

	//Start Menu Number (int)
	data->push_back(this->startMenuNumber & 0xFF);
	data->push_back((this->startMenuNumber >> 8) & 0xFF);
	data->push_back((this->startMenuNumber >> 16) & 0xFF);
	data->push_back((this->startMenuNumber >> 24) & 0xFF);

	//Data Count (Short)
	unsigned int count = this->menuLayouts->size(); //+ all others added on when added

	data->push_back(count & 0xFF);
	data->push_back((count >> 8) & 0xFF);
	data->push_back((count >> 16) & 0xFF);
	data->push_back((count >> 24) & 0xFF);

	//MenuLayout Data
	for(auto menuLayout = this->menuLayouts->begin(); menuLayout < this->menuLayouts->end(); menuLayout++) {
		if((*menuLayout)->ToSaveToData(data) == false) return false;
	}

	return true;
}

bool OSData::GameType::ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations){
	if (images == NULL) return false;
	if (this->menuLayouts == NULL) return false;

	for(auto item = this->menuLayouts->begin(); item < this->menuLayouts->end(); item++) {
		if((*item)->ImageToNumbers(images,imageLocations) == false) return false;
	}
	return true;
}

bool OSData::GameType::LinkNumbers(std::vector<Functions::RGBImage*>* images){
	if (images == NULL) return false;
	for(auto item = this->menuLayouts->begin(); item != this->menuLayouts->end(); item++) {
		if((*item)->LinkNumbers(images) == false) return false;
	}
	return true;
}


std::string OSData::GameType::ToString(){

	std::string data;

	data += "GameName=" + this->gameName + "\n";

	if(this->menuLayouts != NULL){
		for(auto item=this->menuLayouts->begin() ; item < this->menuLayouts->end(); item++ ){
			data += (*item)->ToString();
		}
	}

	return data;
}

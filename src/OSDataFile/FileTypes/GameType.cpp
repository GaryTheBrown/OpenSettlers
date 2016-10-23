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
this->gameName = "";
this->menuLayouts = NULL;
}
OSData::GameType::GameType(std::string gameName,
		std::vector<MenuLayout*>* menuLayouts
//				   GameOptions* gameOptions,
//				   Layout* layout,
//				   MapSetup* mapSetup,
//				   List<Resource>* resourceList,
//				   List<Race>* raceList
				   ):FileTypes(eFull) {
	this->gameName = gameName;
	this->menuLayouts = menuLayouts;
	std::sort(this->menuLayouts->begin(),this->menuLayouts->end());
//	this->gameOptions = gameOptions;
//	this->layout = layout;
//	this->mapSetup = mapSetup;
//	this->resourceList = resourceList;
//	this->raceList = raceList;

}

OSData::GameType::GameType(Functions::DataReader* reader)
	:FileTypes(eMenuLayout){

	unsigned int textSize = reader->ReadChar();
	this->gameName = reader->ReadString(textSize,-1);

	unsigned int itemCount = reader->ReadInt();
	for (unsigned int i = 0; i < itemCount; i++){
		this->fileType = static_cast<FileTypes::eFileType>(reader->ReadShort());
		this->DoFileType(reader);
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
			this->GetFileType((char*)node->children->name);
			this->DoFileType(node->children,true);
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
}

void OSData::GameType::GetFileType(std::string data){
	if (data == "MenuLayout")
		this->fileType = FileTypes::eMenuLayout;
	else if (data == "LoadScreen")
		this->fileType = FileTypes::eLoadScreen;
	else //Includes Full and Archive
		this->fileType = FileTypes::eNone;
}

void OSData::GameType::DoFileType(void* data, bool xml){

	switch(this->fileType){

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

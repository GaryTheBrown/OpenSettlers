/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GameOptions.h"

OSData::GameOptions::GameOptions():FileTypes(eGameOptions){

}

OSData::GameOptions::GameOptions(Functions::DataReader* reader):FileTypes(eGameOptions){
}

OSData::GameOptions::GameOptions(xmlNode* node):FileTypes(eGameOptions){
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
				this->DoFileType(fileType, itemNode);
			itemNode = itemNode->next;
		}
	}
}

OSData::GameOptions::~GameOptions() {

}

void OSData::GameOptions::CheckValues(std::string name, std::string value){
/*
	if (name == "Name")
		this->gameName = value;
	if (name == "StartMenu")
		this->startMenuNumber = atoi(value.c_str());
	if (name == "GameNumber")
		this->gameName = atoi(value.c_str());
*/
}

void OSData::GameOptions::DoFileType(FileTypes::eFileType fileType, void* data){


}
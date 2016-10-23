/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUISpacerData.h"


OSData::GUISpacerData::GUISpacerData(std::pair<unsigned short,unsigned short> size)
:OSData::GUIItemData(GUISpacerType,std::make_pair(0,0),size,GUIItemData::pNone,GUIItemData::pNone){

}

OSData::GUISpacerData::GUISpacerData(Functions::DataReader* reader)
	:OSData::GUIItemData(GUISpacerType,std::make_pair(0,0),std::make_pair(0,0),GUIItemData::pNone,GUIItemData::pNone){

	this->APIVersion = reader->ReadInt();

	if (this->APIVersion > APILEVEL::GUIITEMS){
			LOGSYSTEM->Error("Item API is Newer than Game API:" + Functions::ToString(this->APIVersion) + ">" + Functions::ToString(APILEVEL::GUIITEMS));
			 this->fileOK = false;
			 return;
	}
	this->size.first = reader->ReadShort();
	this->size.second = reader->ReadShort();
}

OSData::GUISpacerData::GUISpacerData(xmlNode* node)
:GUIItemData(GUISpacerType,std::make_pair(0,0),std::make_pair(0,0),GUIItemData::pNone,GUIItemData::pNone){
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
	}
}
void OSData::GUISpacerData::CheckValues(std::string name, std::string value){
	if (name == "HorizontalSize")
		this->size.first = atoi(value.c_str());
	else if (name == "VerticalSize")
		this->size.second = atoi(value.c_str());
}

bool OSData::GUISpacerData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	return GUIItemData::ToSaveToData(data);
}

std::string OSData::GUISpacerData::ToString(){
	std::string data;
	data += "GUISpacer\n";
	data += "Size.X = " + Functions::ToString(this->size.first) + "\n";
	data += "Size.Y = " + Functions::ToString(this->size.second) + "\n";;
	return data;
}

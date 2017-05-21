/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MenuLayout.h"

OSData::MenuLayout::MenuLayout(unsigned int menuID,std::string title,RGBA backgroundColour,std::vector<GUIItemData*>* itemData)
	:FileTypes(eMenuLayout),
	 menuID(menuID),
	 title(title),
	 backgroundColour(backgroundColour),
	 itemData(itemData){
}

OSData::MenuLayout::MenuLayout(Functions::DataReader* reader):FileTypes(eMenuLayout){
	this->APIVersion = reader->ReadInt();
	if (this->APIVersion > APILEVEL::MENULAYOUT){
		LOGSYSTEM->Error(reader->FileName() + "is Newer than MenuLayout API:" + Functions::ToString(this->APIVersion) + ">" + Functions::ToString(APILEVEL::MENULAYOUT));
		 return;
	}

	this->menuID = reader->ReadInt();
	unsigned int textSize = reader->ReadChar();

	this->title = reader->ReadString(textSize);

	this->backgroundColour = reader->ReadInt();

	unsigned short dataCount = reader->ReadShort();
	this->itemData = new std::vector<GUIItemData*>();

	GUIItemData::eGUIItemType itemDataType;
	for(int i = 0; i < dataCount;i++){
		itemDataType = static_cast<GUIItemData::eGUIItemType>(reader->ReadChar());
		this->itemData->push_back(DoItemType(itemDataType,reader));
	}
}

OSData::MenuLayout::MenuLayout(xmlNode* node):FileTypes(eMenuLayout){
	xmlAttr* xmlAttribute = node->properties;
	while(xmlAttribute){
		this->CheckValues(((char*)xmlAttribute->name),((char*)xmlAttribute->children->content));
		xmlAttribute = xmlAttribute->next;
	}

	xmlNode* itemNode = node->children;
	if(itemNode != NULL){
		this->itemData = new std::vector<GUIItemData*>();
		while(itemNode){
			GUIItemData::eGUIItemType itemDataType = GetItemType((char*)itemNode->name);
			if (itemDataType != GUIItemData::GUINoneType)
				this->itemData->push_back(DoItemType(itemDataType,itemNode,true));
			itemNode = itemNode->next;
		}

	}

}

OSData::MenuLayout::~MenuLayout(){
	if(this->itemData != NULL){
		for(auto item=this->itemData->begin() ; item < this->itemData->end(); item++ ){
			delete (*item);
		}
		this->itemData->clear();
		delete this->itemData;
	}
}

void OSData::MenuLayout::CheckValues(std::string name, std::string value){
	if (name ==  "MenuID")
		this->menuID = atoi(value.c_str());
	else if (name ==  "Title")
		this->title = value;
	else if (name ==  "BackgroundColour")
		this->backgroundColour = Functions::StringToHex(value);
}

bool OSData::MenuLayout::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;

	FileTypes::ToSaveToData(data);

	//API Version (int)
	data->push_back(this->APIVersion & 0xFF);
	data->push_back((this->APIVersion >> 8) & 0xFF);
	data->push_back((this->APIVersion >> 16) & 0xFF);
	data->push_back((this->APIVersion >> 24) & 0xFF);

	//Menu ID (int)
	data->push_back(this->menuID & 0xFF);
	data->push_back((this->menuID >> 8) & 0xFF);
	data->push_back((this->menuID >> 16) & 0xFF);
	data->push_back((this->menuID >> 24) & 0xFF);

	//text Size (char)
	data->push_back(static_cast<char>(this->title.size()));
	//Text
	std::copy(this->title.begin(), this->title.end(), std::back_inserter(*data));


	//Background Colour (INT/4 char)
	data->push_back(this->backgroundColour.A);
	data->push_back(this->backgroundColour.B);
	data->push_back(this->backgroundColour.G);
	data->push_back(this->backgroundColour.R);

	//Data Count (Short)
	unsigned short count = this->itemData->size();
	data->push_back(count & 0xFF);
	data->push_back((count >> 8) & 0xFF);

	//Data
	for(auto item = this->itemData->begin(); item < this->itemData->end(); item++) {
		if((*item)->ToSaveToData(data) == false) return false;
	}

	return true;
}

bool OSData::MenuLayout::ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations){
	if ((images == NULL)||(this->itemData == NULL)) return false;

	for(auto item = this->itemData->begin(); item < this->itemData->end(); item++) {
		if((*item)->ImageToNumbers(images,imageLocations) == false) return false;
	}
	return true;
}

bool OSData::MenuLayout::LinkNumbers(std::vector<Functions::RGBImage*>* images){
	if (images == NULL) return false;
	for(auto item = this->itemData->begin(); item != this->itemData->end(); item++) {
		if((*item)->LinkNumbers(images) == false) return false;
	}
	return true;
}

std::string OSData::MenuLayout::ToString(){
	std::string data;

	data += "MENULAYOUT:" + Functions::ToString(this->menuID) + "\n";
	data += "Title = " + this->title + "\n";
	data += "Background Colour = " + Functions::ToHex(this->backgroundColour.ReturnInt(),4) + "\n";

	if (this->itemData != NULL){
		for(auto item = this->itemData->begin(); item != this->itemData->end(); item++) {
			data += (*item)->ToString();
		}
	}

	return data;
}

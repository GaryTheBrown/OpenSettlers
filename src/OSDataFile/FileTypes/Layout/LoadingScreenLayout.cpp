/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "LoadingScreenLayout.h"

OSData::LoadingScreenLayout::LoadingScreenLayout(unsigned int menuID,std::string title,RGBA backgroundColour,std::vector<GUIImageData*>* imageData)
	:FileTypes(eLoadingScreenLayout),
	 menuID(menuID),
	 title(title),
	 backgroundColour(backgroundColour),
	 imageData(imageData){
}

OSData::LoadingScreenLayout::LoadingScreenLayout(Functions::DataReader* reader):FileTypes(eLoadingScreenLayout){
	this->APIVersion = reader->ReadInt();
	if (this->APIVersion > APILEVEL::LOADINGSCREENLAYOUT){
		LOGSYSTEM->Error(reader->FileName() + "is Newer than LoadingScreenLayout API:" + Functions::ToString(this->APIVersion) + ">" + Functions::ToString(APILEVEL::LOADINGSCREENLAYOUT));
		 return;
	}

	this->menuID = reader->ReadInt();
	unsigned int textSize = reader->ReadChar();

	this->title = reader->ReadString(textSize);

	this->backgroundColour = reader->ReadInt();

	unsigned short dataCount = reader->ReadShort();
	this->imageData = new std::vector<GUIImageData*>();

	for(int i = 0; i < dataCount;i++){
		//imageDataType = static_cast<GUIImageData::eGUIItemType>(reader->ReadChar());
		this->imageData->push_back(new GUIImageData(reader));
	}
}

OSData::LoadingScreenLayout::LoadingScreenLayout(xmlNode* node):FileTypes(eLoadingScreenLayout){
	xmlAttr* xmlAttribute = node->properties;
	while(xmlAttribute){
		this->CheckValues(((char*)xmlAttribute->name),((char*)xmlAttribute->children->content));
		xmlAttribute = xmlAttribute->next;
	}

	xmlNode* itemNode = node->children;
	if(itemNode != NULL){
		this->imageData = new std::vector<GUIImageData*>();
		while(itemNode){
			//GUIImageData::eGUIItemType imageDataType = GetItemType((char*)itemNode->name);
			//if (imageDataType != GUIImageData::GUINoneType)
				this->imageData->push_back(new GUIImageData(itemNode));
			itemNode = itemNode->next;
		}

	}

}

OSData::LoadingScreenLayout::~LoadingScreenLayout(){
	if(this->imageData != NULL){
		for(auto item=this->imageData->begin() ; item < this->imageData->end(); item++ ){
			delete (*item);
		}
		this->imageData->clear();
		delete this->imageData;
	}
}

void OSData::LoadingScreenLayout::CheckValues(std::string name, std::string value){
	if (name ==  "MenuID")
		this->menuID = atoi(value.c_str());
	else if (name ==  "Title")
		this->title = value;
	else if (name ==  "BackgroundColour")
		this->backgroundColour = Functions::StringToHex(value);
}

bool OSData::LoadingScreenLayout::ToSaveToData(std::vector<char>* data){
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
	unsigned short count = this->imageData->size();
	data->push_back(count & 0xFF);
	data->push_back((count >> 8) & 0xFF);

	//Data
	for(auto item = this->imageData->begin(); item < this->imageData->end(); item++) {
		if((*item)->ToSaveToData(data) == false) return false;
	}

	return true;
}

bool OSData::LoadingScreenLayout::ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations){
	if ((images == NULL)||(this->imageData == NULL)) return false;

	for(auto item = this->imageData->begin(); item < this->imageData->end(); item++) {
		if((*item)->ImageToNumbers(images,imageLocations) == false) return false;
	}
	return true;
}

bool OSData::LoadingScreenLayout::LinkNumbers(std::vector<Functions::RGBImage*>* images){
	if (images == NULL) return false;
	for(auto item = this->imageData->begin(); item != this->imageData->end(); item++) {
		if((*item)->LinkNumbers(images) == false) return false;
	}
	return true;
}

std::string OSData::LoadingScreenLayout::ToString(){
	std::string data;

	data += "LOADINGSCREENLAYOUT:" + Functions::ToString(this->menuID) + "\n";
	data += "Title = " + this->title + "\n";
	data += "Background Colour = " + Functions::ToHex(this->backgroundColour.ReturnInt(),4) + "\n";

	if (this->imageData != NULL){
		for(auto item = this->imageData->begin(); item != this->imageData->end(); item++) {
			data += (*item)->ToString();
		}
	}

	return data;
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIBoxData.h"

OSData::GUIBoxData::GUIBoxData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition, RGBA backgroundColour, eBoxType boxType, std::vector<GUIItemData*>* itemDataList,bool multiSelect)
	:OSData::GUIItemData(GUIBoxType,location,size,verticalPosition,horizontalPosition){
	this->backgroundColour = backgroundColour;
	this->boxType = boxType;
    this->itemData = itemDataList;
    this->multiSelect = multiSelect;
}

OSData::GUIBoxData::GUIBoxData(Functions::DataReader* reader)
	:OSData::GUIItemData(GUIBoxType,reader){

	this->backgroundColour = reader->ReadInt();
	this->boxType = static_cast<eBoxType>(reader->ReadShort());
	this->multiSelect = reader->ReadChar() & 1;

	unsigned short count = reader->ReadShort();
	this->itemData = new std::vector<GUIItemData*>(count);
	eGUIItemType itemDataType;
	GUIItemData* item;

	for (unsigned char i = 0; i < count; i++){
		itemDataType = static_cast<eGUIItemType>(reader->ReadShort());
		switch(itemDataType){
		case GUIImageType:
			item = new GUIImageData(reader);
			break;
		case GUIButtonType:
			item = new GUIButtonData(reader);
			break;
		case GUITextType:
			item = new GUITextData(reader);
			break;
		case GUIBoxType:
			item = new GUIBoxData(reader);
			break;
		case GUINoneType:
			break;
		}
		if(item != NULL){
			this->itemData->push_back(item);
			item = NULL;
		}
	}
}
OSData::GUIBoxData::GUIBoxData(std::string line):GUIItemData(GUIButtonType,line){
	this->boxType = Empty;
	this->itemData = NULL;
	this->multiSelect = false;

	//extract special () buttons/Images
	size_t posOpen, posClose;

	posOpen = line.find_first_of('(');
	posClose = line.find_first_of(')');
	std::string* item;
	std::vector<std::string*>* items = new std::vector<std::string*>();
	while(posClose < line.length()){
		item = new std::string(line.substr(posOpen,posClose));
		line.erase(posOpen,(posClose - posOpen));
		posOpen = line.find_first_of('(');
		posClose = line.find_first_of(')');
		items->push_back(item);
	}

	std::vector<std::pair<std::string,std::string>>* loadDataList = Functions::LoadFromTextLine(line);

	for(unsigned int i = 0; i < loadDataList->size();i++){
		if (loadDataList->at(i).first == "ListBoxType")
			this->boxType = (eBoxType)atoi(loadDataList->at(i).second.c_str());
		if (loadDataList->at(i).first == "BackgroundColour"){
			//Special
			std::string line = loadDataList->at(i).second;
			int pos = line.find_first_of('-');
			this->backgroundColour.R = (unsigned char)atoi(line.substr(0, pos).c_str());
			std::string line2 = line.substr(pos+1);
			pos = line2.find_first_of('-');
			this->backgroundColour.G = (unsigned char)atoi(line2.substr(0, pos).c_str());
			std::string line3 = line.substr(pos+1);
			pos = line3.find_first_of('-');
			this->backgroundColour.B = (unsigned char)atoi(line3.substr(0, pos).c_str());
			this->backgroundColour.A = (unsigned char)atoi(line3.substr(pos+1).c_str());
		}
		if (loadDataList->at(i).first == "MultiSelect")
			this->multiSelect = loadDataList->at(i).second=="true"?true:false;

	}

	delete loadDataList;

	size_t posEquals;
	std::string type;
	GUIItemData* itemData;
	for(unsigned int i = 0; i < items->size();i++){
		posEquals = items->at(i)->find_first_of('=');
		type = items->at(i)->substr(0,posEquals);
		items->at(i)->erase(0,posEquals);
		if (type == "Button"){
			if (this->itemData == NULL) this->itemData = new std::vector<GUIItemData*>();
			itemData = new GUIButtonData(*items->at(i));
		}
		if (type == "Image"){
			if (this->itemData == NULL) this->itemData = new std::vector<GUIItemData*>();
			itemData = new GUIImageData(*items->at(i));

		}

		if(item != NULL)
			this->itemData->push_back(itemData);
	}
}

bool OSData::GUIBoxData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	if (GUIItemData::ToSaveToData(data) == false) return false;

	//Background Colour (Int)(RGBA)
	data->push_back(this->backgroundColour.R);
	data->push_back(this->backgroundColour.G);
	data->push_back(this->backgroundColour.B);
	data->push_back(this->backgroundColour.A);

	//Box Type (Short)(eBoxType)
	data->push_back(static_cast<char>(this->boxType));

	//Multi Select (Bool)
	data->push_back(static_cast<char>(this->multiSelect?1:0));

	//Item count (Char)
	unsigned char count = this->itemData->size();
	data->push_back(count & 0xFF);
	//All Items Here
	for(std::vector<GUIItemData*>::iterator item = this->itemData->begin(); item != this->itemData->end(); item++) {
		(*item)->ToSaveToData(data);
	}

	return true;
}

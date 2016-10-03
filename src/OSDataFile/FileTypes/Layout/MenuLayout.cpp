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

OSData::MenuLayout::MenuLayout(int menuID,std::string title,RGBA backgroundColour,std::vector<GUIItemData*>* itemData)
	:FileTypes(eMenuLayout),
	 menuID(menuID),
	 title(title),
	 backgroundColour(backgroundColour),
	 itemData(itemData){
}

OSData::MenuLayout::MenuLayout(Functions::DataReader* reader)
	:FileTypes(eMenuLayout){
	this->APIVersion = reader->ReadInt();
	if (this->APIVersion > APILEVEL::MENULAYOUT){
		LOGSYSTEM->Error(reader->FileName() + "is Newer than Game API:" + Functions::ToString(this->APIVersion) + ">" + Functions::ToString(APILEVEL::MASTER));
		 this->fileOK = false;
		 return;
	}

	this->menuID = reader->ReadInt();

	unsigned int textSize = reader->ReadChar();
	this->title = reader->ReadString(textSize,-1);

	this->backgroundColour = reader->ReadInt();

	unsigned short dataCount = reader->ReadShort();
	this->itemData = new std::vector<GUIItemData*>(dataCount);

	GUIItemData::eGUIItemType itemDataType;
	GUIItemData* item = NULL;;
	for(int i = 0; i < dataCount;i++){
		itemDataType = static_cast<GUIItemData::eGUIItemType>(reader->ReadChar());
		switch(itemDataType){
		case GUIItemData::GUIImageType:
			item = new GUIImageData(reader);
			break;
		case GUIItemData::GUIButtonType:
			item = new GUIButtonData(reader);
			break;
		case GUIItemData::GUITextType:
			item = new GUITextData(reader);
			break;
		case GUIItemData::GUIBoxType:
			item = new GUIBoxData(reader);
			break;
		case GUIItemData::GUINoneType:
			break;
		}
		if (item != NULL){
			this->itemData->push_back(item);
			item = NULL;
		}
	}
//read rest of data from file
}

OSData::MenuLayout::MenuLayout(std::string file)
	:FileTypes(eMenuLayout),
 	 menuID(0),
	 backgroundColour(0,0,0,0){

	std::vector<std::pair<std::string,std::string>>* loadDataList = Functions::LoadFromTextFile(file);


	for(unsigned int i = 0; i < loadDataList->size();i++){

		if (loadDataList->at(i).first == "MenuID")
			this->menuID = atoi(loadDataList->at(i).second.c_str());
		if (loadDataList->at(i).first == "Title")
			this->title = loadDataList->at(i).second;
		if (loadDataList->at(i).first == "BackgroundColour"){
			std::string line = loadDataList->at(i).second;
			int pos = line.find_first_of(',');
			int pos2 = line.find_first_of(',',pos+1);
			this->backgroundColour.R = atoi(line.substr(0, pos).c_str());
			this->backgroundColour.G = atoi(line.substr(pos+1, pos2).c_str());
			this->backgroundColour.B = atoi(line.substr(pos2+1).c_str());
		}
		if (loadDataList->at(i).first == "ImageData"){
			if(this->itemData == NULL) this->itemData = new std::vector<GUIItemData*>();
			GUIImageData* newImageData = new GUIImageData(loadDataList->at(i).second);
			this->itemData->push_back(newImageData);
		}
		if (loadDataList->at(i).first == "ButtonData"){
			if(this->itemData == NULL) this->itemData = new std::vector<GUIItemData*>();
			GUIButtonData* newButtonData = new GUIButtonData(loadDataList->at(i).second);
			this->itemData->push_back(newButtonData);
		}
		if (loadDataList->at(i).first == "TextData"){
			if(this->itemData == NULL) this->itemData = new std::vector<GUIItemData*>();
			GUITextData* newTextData = new GUITextData(loadDataList->at(i).second);
			this->itemData->push_back(newTextData);
		}
		if (loadDataList->at(i).first == "ListBoxData"){
			if(this->itemData == NULL) this->itemData = new std::vector<GUIItemData*>();
			GUIBoxData* newBoxData = new GUIBoxData(loadDataList->at(i).second);
			this->itemData->push_back(newBoxData);
		}
	}

	delete loadDataList;

}

OSData::MenuLayout::~MenuLayout() {
	if(this->itemData != NULL){
		for (unsigned int i = 0; i < this->itemData->size(); i++){
			delete this->itemData->at(i);
		}
		delete this->itemData;
	}
}

bool OSData::MenuLayout::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	FileTypes::ToSaveToData(data);

	//Menu ID (int)
	data->push_back((this->menuID >> 24) & 0xFF);
	data->push_back((this->menuID >> 16) & 0xFF);
	data->push_back((this->menuID >> 8) & 0xFF);
	data->push_back(this->menuID & 0xFF);

	//text Size (char)
	data->push_back(static_cast<char>(this->title.size()));
	//Text
	std::copy(this->title.begin(), this->title.end()-1, std::back_inserter(*data));


	//Background Colour (INT/4 char)
	data->push_back(this->backgroundColour.R);
	data->push_back(this->backgroundColour.G);
	data->push_back(this->backgroundColour.B);
	data->push_back(this->backgroundColour.A);


	//Data Count (Short)
	unsigned short count = this->itemData->size();
	data->push_back((count >> 8) & 0xFF);
	data->push_back(count & 0xFF);

	//Data
	for(std::vector<GUIItemData*>::iterator item = this->itemData->begin(); item != this->itemData->end(); item++) {
		(*item)->ToSaveToData(data);
	}

	return false;
}

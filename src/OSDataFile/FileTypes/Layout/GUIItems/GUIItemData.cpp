/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIItemData.h"

OSData::GUIItemData::GUIItemData(eGUIItemType itemType,std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition)
	:itemType(itemType),
	location(location),
	size(size),
	verticalPosition(verticalPosition),
	horizontalPosition(horizontalPosition){
}

OSData::GUIItemData::GUIItemData(eGUIItemType itemType,Functions::DataReader* reader){
	this->itemType = itemType;
	this->APIVersion = reader->ReadInt();
	if (this->APIVersion > APILEVEL::MASTER){
			LOGSYSTEM->Error("Item API is Newer than Game API:" + Functions::ToString(this->APIVersion) + ">" + Functions::ToString(APILEVEL::MASTER));
			 this->fileOK = false;
			 return;
	}
	this->location.first = reader->ReadShort();
	this->location.second = reader->ReadShort();
	this->size.first = reader->ReadShort();
	this->size.second = reader->ReadShort();
	this->verticalPosition = static_cast<ePosition>(reader->ReadChar());
	this->horizontalPosition = static_cast<ePosition>(reader->ReadChar());
}
OSData::GUIItemData::GUIItemData(eGUIItemType itemType,std::string line){
	this->itemType = itemType;
	this->verticalPosition = pNone;
	this->horizontalPosition = pNone;
	this->location = {0,0};

	std::vector<std::pair<std::string,std::string>>* loadDataList = Functions::LoadFromTextLine(line);

	for(unsigned int i = 0; i < loadDataList->size();i++){

		if (loadDataList->at(i).first == "VerticalPosition")
			this->verticalPosition = static_cast<ePosition>(atoi(loadDataList->at(i).second.c_str()));
		if (loadDataList->at(i).first == "HorizontalPosition")
			this->horizontalPosition = static_cast<ePosition>(atoi(loadDataList->at(i).second.c_str()));
		if (loadDataList->at(i).first == "VerticalLocation")
			this->location.second = atoi(loadDataList->at(i).second.c_str());
		if (loadDataList->at(i).first == "HorizontalLocation")
			this->location.first = atoi(loadDataList->at(i).second.c_str());
		if (loadDataList->at(i).first == "VerticalSize")
			this->size.second = atoi(loadDataList->at(i).second.c_str());
		if (loadDataList->at(i).first == "HorizontalSize")
			this->size.first = atoi(loadDataList->at(i).second.c_str());
	}

	delete loadDataList;
}

bool OSData::GUIItemData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) return false;
	// This order
	//itemType (char)
	data->push_back(static_cast<char>(this->itemType));
	//location.first (Short)
	data->push_back((this->location.first >> 8) & 0xFF);
	data->push_back(this->location.first & 0xFF);

	//location.second (Short)
	data->push_back((this->location.second >> 8) & 0xFF);
	data->push_back(this->location.second & 0xFF);

	//size.first (Short)
	data->push_back((this->size.first >> 8) & 0xFF);
	data->push_back(this->size.first & 0xFF);

	//size.second (Short)
	data->push_back((this->size.second >> 8) & 0xFF);
	data->push_back(this->size.second & 0xFF);

	//Vertical Position (Char)
	data->push_back(static_cast<char>(this->verticalPosition));
	//Horizontal Position (Char)
	data->push_back(static_cast<char>(this->horizontalPosition));

	return true;
}

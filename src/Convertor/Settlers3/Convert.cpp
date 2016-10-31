/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Convert.h"

Converter::Settlers3::Convert::Convert(std::string locationOfFiles, bool gog){
	this->data.locationofFiles = locationOfFiles;
	this->GUIFunctions = new ConvertGUI(&data);
	this->data.version = Extractor::Settlers3::CheckGameVersion(locationOfFiles, gog);
	this->SetupData();
}

Converter::Settlers3::Convert::~Convert(){
	delete this->GUIFunctions;
}

OSData::GameType* Converter::Settlers3::Convert::DoConvert(){
	if (this->somethingToExtract == false) return NULL;
	OSData::GameType* gameType = new OSData::GameType("The Settlers 3",0);
	//Menus First
	this->GUIFunctions->Original(gameType);
	return gameType;
}

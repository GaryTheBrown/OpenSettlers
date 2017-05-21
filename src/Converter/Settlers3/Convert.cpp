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

Converter::Settlers3::Convert::Convert(std::string locationOfFiles, bool gog,std::string saveLocation){
	this->data.locationofFiles = locationOfFiles;
	this->saveLocation = saveLocation;
	this->GUIFunctions = new ConvertGUI(&data);
	this->data.version = Extractor::Settlers3::CheckGameVersion(locationOfFiles, gog);
	this->SetupData();
}

Converter::Settlers3::Convert::~Convert(){
	if (this->GUIFunctions != NULL)
		delete this->GUIFunctions;

	if(Functions::FolderExists("EXE")){
		LOGSYSTEM->Log("Cleaning up Extracted Cab Data",1);
		Functions::RemoveFolder("EXE");
	}
	if(Functions::FolderExists("app")){
		LOGSYSTEM->Log("Cleaning up Extracted GOG Data",1);
		Functions::RemoveFolder("app");
		Functions::RemoveFolder("sys");
		Functions::RemoveFolder("tmp");
		if(Functions::FolderExists("commonappdata")) Functions::RemoveFolder("commonappdata");
	}

}

bool Converter::Settlers3::Convert::DoConvert(){
	if (this->somethingToExtract == false) return NULL;
	OSData::GameType* gameType = NULL;
	OSData::File* file = NULL;

	if (Functions::FileExists(this->saveLocation + "/" + this->saveGameName + ".dat")){
		file = new OSData::File(this->saveLocation + "/" + this->saveGameName + ".dat");
		gameType = file->ReturnGameType();
	}else{
		gameType = new OSData::GameType(this->gameName,3,OSData::eS3None,3);
	}
	//Menus First
	this->GUIFunctions->Original(gameType);
	this->GUIFunctions->MissionCD(gameType);
	this->GUIFunctions->Amazon(gameType);
	this->GUIFunctions->Gold(gameType);

	//Sort Data
	gameType->SortAll();

	//TODO:Update Addons
	gameType->AddonsIncluded(this->data.addons);

	if (file == NULL) file = new OSData::File(gameType);
	file->ImageDataToNumbers();
	file->ToSaveToData(this->saveLocation + "/" + this->saveGameName);
	delete file;

	return true;
}

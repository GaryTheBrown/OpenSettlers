/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "main.h"

int main(int argc,char* argv[]){

	ConfigList* configList = new ConfigList();
	unsigned int configLocationSize = 2;
	std::string configLocations[configLocationSize] = {"config.cfg", "~/Opensettlers/config.cfg"};
	for(unsigned int i = 0; i < configLocationSize; i++){
		if(Functions::FileExists(configLocations[i])){
			if(!configList->ConfigFile(configLocations[i])) return 0;
		}
	}
	//Startup Arguments Setup
	StartupArguments* startupArguments = new StartupArguments(argc,argv);
	if(startupArguments->CheckArguments(configList))
		return 0; //if comes back true exits

	OSData::GameType* gameType = NULL;
	OSData::File* file = NULL;
	ReturnData startMenuReturn = ReturnData(MMStartMenu);
///CLI FUNCTIONS
	//CLI Converter
	if(startupArguments->Converter()){
		LOGSYSTEM->Log("Open Settlers Converter Started",1);
		if(startupArguments->OutputLocation() == ""){
			if (Converter::Main(startupArguments->Location(),configList->GetValue<std::string>("gameslocation")) == false) return 1;
		}else{
			if (Converter::Main(startupArguments->Location(),startupArguments->OutputLocation()) == false) return 1;
		}
		LOGSYSTEM->Log("Open Settlers Converter Completed",1);
		return 0;
	}
	//CLI Extractor
	if(startupArguments->Extractor()){
		LOGSYSTEM->Log("Open Settlers Extractor Started",1);
		if(startupArguments->OutputLocation() == ""){
			if (Extractor::Main(startupArguments->Location()) == false) return 1;
		}else{
			if (Extractor::Main(startupArguments->Location(),startupArguments->OutputLocation()) == false) return 1;
		}
		LOGSYSTEM->Log("Open Settlers Extractor Completed",1);
		return 0;
	}
	//TODO Create a Function to call for this to keep it clean
	if(startupArguments->Test()){ //Temp XML To Dat FUNCTION OR DAT READER.
		LOGSYSTEM->Log("Open Settlers Test Started",1);

		file = new OSData::File(startupArguments->Location());

		std::string extension = startupArguments->Location().substr(startupArguments->Location().find_last_of(".") + 1);
		std::transform(extension.begin(), extension.end(), extension.begin(), toupper);
		if (extension == "XML"){
			//Change Locations To Internal Images
			file->ImageLocationsToNumbers();
		}else{
			//Print To Screen
			std::cout << file->ToString();
		}
		//Save Section
		if (extension == "XML"){
			std::string fileWithoutExtension = startupArguments->Location().substr(0, startupArguments->Location().find_last_of("."));
			file->ToSaveToData(fileWithoutExtension);
		}

		delete file;

		LOGSYSTEM->Log("Open Settlers Test Completed",1);
		return 0;
	}

	SystemInterface::System* system;
	std::string windowName = PACKAGE_NAME;

//GRAPHICAL FUNCTIONS
//SETUP SYSTEM


	switch(startupArguments->SystemType()){
	case StartupArguments::ST_SDL2://MAYBE REMOVE THIS?
		system = new SystemInterface::SDL2System(windowName,configList);
		break;
	case StartupArguments::ST_OGL21:
		system = new SystemInterface::OGL21System(windowName,configList);
		break;
	default:
		LOGSYSTEM->Error("System Interface Not Recognised Quitting");
		return 1;
	}


	while(startMenuReturn.MenuEvent() != MMQuit){

		//If not loading Game From command then Run Start Menu
		if(gameType == NULL){
			//Create Start Menu Object
			StartMenu* startMenu = new StartMenu(system,configList);
			//Load The Startmenu or die
			if(!startMenu->Load()) return 1;
			//DO StartMenu Loop
			startMenuReturn = startMenu->Loop();
			// Cleanup window
			delete startMenu;
		}
		switch(startMenuReturn.MenuEvent()){
		case MMStartGame:{
			file = new OSData::File(configList->GetValue<std::string>("gameslocation") + startMenuReturn.String());
			gameType = file->ReturnGameType();
			GameInterface::Game* game = new GameInterface::Game(system,configList,gameType);
			system->display->SetWindowName(std::string(PACKAGE_NAME) + "- " + gameType->GameName());
			startMenuReturn = game->Loop();
			delete game;
			return 0;
		}
		default:
			break;
		}
	}
	LOGSYSTEM->Log("Closing Down");
	if (file != NULL) delete file;
	if (system != NULL) delete system;
	if (startupArguments != NULL) delete startupArguments;
	if (configList != NULL) delete configList;
	return 0;
}

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

	//Startup Arguments Setup
	StartupArguments* startupArguments = new StartupArguments(argc,argv);
	if(startupArguments->CheckArguments())
		return 0; //if comes back true exits

	OSData::GameType* gameType = NULL;
	OSData::File* file = NULL;
	GFXInterface::GFXReturn startMenuReturn = GFXInterface::GFXReturn(MMStartMenu);
///CLI FUNCTIONS
	//CLI Converter
	if(startupArguments->Converter()){
		LOGSYSTEM->Log("Open Settlers Converter Started",1);
		if (Converter::Main(startupArguments->Location()) == false) return 1;
		LOGSYSTEM->Log("Open Settlers Converter Completed",1);
		return 0;
	}
	//CLI Extractor
	if(startupArguments->Extractor()){
		LOGSYSTEM->Log("Open Settlers Extractor Started",1);
		if (Extractor::Main(startupArguments->Location()) == false) return 1;
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
	std::string windowName = ENGINENAME;

//GRAPHICAL FUNCTIONS
//SETUP SYSTEM
	switch(startupArguments->SystemType()){
	case StartupArguments::ST_SDL2://BROKEN MAYBE REMOVE THIS?
		system = new SystemInterface::SDL2System(windowName,startupArguments->WindowSize(),startupArguments->Fullscreen());
		break;
	case StartupArguments::ST_OGL21:
		system = new SystemInterface::OGL21System(windowName,startupArguments->WindowSize(),startupArguments->Fullscreen());
		break;
	default:
		LOGSYSTEM->Error("System Interface Not Recognised Quitting");
		return 1;
	}


	while(startMenuReturn.MenuEvent() != MMQuit){

		//If not loading Game From command then Run Start Menu
		if(gameType == NULL){
			//Create Start Menu Object
			StartMenu* startMenu = new StartMenu(system);
			//DO StartMenu Loop
			startMenuReturn = startMenu->Loop();
			// Cleanup window
			delete startMenu;
		}
		switch(startMenuReturn.MenuEvent()){
		case MMStartGame:{
			file = new OSData::File("Games/" + startMenuReturn.String());
			gameType = file->ReturnGameType();
			GameInterface::Game* game = new GameInterface::Game(system,gameType);
			system->display->SetWindowName(ENGINENAME + " - " + gameType->GameName());
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
	return 0;
}

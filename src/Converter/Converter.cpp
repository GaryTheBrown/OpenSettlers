/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Converter.h"

bool Converter::Main(std::string location,std::string saveLocation){
	char gameNo = 0;
	bool GOG = false;

	//First check if location is a file (with extension)
	std::string extension = location.substr(location.find_last_of(".") + 1);
	std::transform(extension.begin(), extension.end(), extension.begin(), toupper);

	if ((location.find_last_of(".") != std::string::npos)&&(extension.length() == 3)){//File with 3 letter extension name
		//GOG EXE's
		if (extension == "EXE"){
			if ((gameNo != 2)&&(gameNo != 3)&&(gameNo != 4)){
				LOGSYSTEM->Log("Reading GOG EXE File",1);

				Functions::ExternalProgram* program = new Functions::ExternalProgram(&location);
				std::string returnstring = program->GOGGameCheck();

				int spos = returnstring.find("\"") + 1;
				int epos = returnstring.find_last_of("\"");

				std::string gameName = returnstring.substr(spos, (epos - spos));

				if (gameName == "Settlers 2 GOLD"){
					gameNo = 2;
				}else if (gameName == "The Settlers 3 - Ultimate Collection"){
					gameNo = 3;
				}else if (gameName == "The Settlers IV GOLD"){
					gameNo = 4;
				}
				delete program;
			}
			GOG = true;
		}
	}
	//If not a file then treat as a folder
	else{
		if(location.find_last_of("/") != location.length()-1) location += "/";

		if(gameNo == 0){
			LOGSYSTEM->Log("Reading Location:"+location,1);
			//if Settlers 1
			if(Functions::FileExists(location + "SETTLER.BAT")){
				gameNo = 1;
			}
			//if Settlers 2
			else if((Functions::FolderExists(location + "s2"))||
					(Functions::FileExists(location + "S2.EXE"))){
				gameNo = 2;
			}
			//if Settlers 3
			else if((Functions::FolderExists(location + "s3"))||(Functions::FileExists(location + "s3.exe"))
					||(Functions::FileExists(location + "S3.EXE"))||(Functions::FolderExists(location + "s3update"))
					||(Functions::FolderExists(location + "S3UPDATE"))){
				gameNo = 3;
			}
			//if Settlers 4
			else if((Functions::FolderExists(location + "s4"))||(Functions::FolderExists(location + "S4"))
					||(Functions::FileExists(location + "s4.exe"))||(Functions::FileExists(location + "S4.exe"))
					||(Functions::FileExists(location + "S4_Main.exe"))){
				gameNo = 4;
			}
		}
	}
	//Make sure a Game Number has been selected
	if ((gameNo == 0)||(gameNo >= 5)){
		LOGSYSTEM->Error("Game Number Not found");
		return false;
	}

	if(!Functions::FolderExists(saveLocation)){
		Functions::CreateDir(saveLocation);
	}

	switch(gameNo){
		case 1:{
			LOGSYSTEM->Log("Settlers 1 Detected.",1);
			LOGSYSTEM->Error("Settlers 1 not implemented yet.");
			return true;
		}
		case 2:{
			LOGSYSTEM->Log("Settlers 2 Detected.",1);
			LOGSYSTEM->Error("Settlers 2 not implemented yet.");
			return true;
		}
		case 3:{
			LOGSYSTEM->Log("Settlers 3 Detected.",1);
			Settlers3::Convert* s3Converter = new Settlers3::Convert(location,GOG,&saveLocation);
			bool passed = s3Converter->DoConvert();
			delete s3Converter;
			return passed;
		}
		case 4:{
			LOGSYSTEM->Log("Settlers 4 Detected.",1);
			LOGSYSTEM->Error("Settlers 4 not implemented yet.");
			return true;
		}
		default:{
			// If nothing above found then
			LOGSYSTEM->Error("No game Detected.");
			return false;
		}
	}

	return false;
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "main_Extractor.h"
namespace Extractor{
	bool Main(std::string location, eType fileType, char gameNo){
		bool GOG = false;
//First check if location is a file (with extension)
		size_t locationofdot = location.find_last_of(".");
		std::string extension = location.substr(locationofdot + 1);

		if ((locationofdot != std::string::npos)&&(extension.length() == 3)){//File with 3 letter extension name
			if ((extension == "map")||(extension == "MAP")){
				fileType = MAP;
				gameNo = 3;
			}
			else if ((extension == "dat")||(extension == "DAT")) {
				fileType = GFX;
				gameNo = 3;
				//TODO check if SND or GFX HERE

			}
			else if ((extension == "exe")||(extension == "EXE")){
				if ((gameNo != 2)&&(gameNo != 3)&&(gameNo != 4)){
					LOGSYSTEM->Log("Reading GOG EXE File",1);

					Functions::ExternalProgram* program = new Functions::ExternalProgram(location);
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
		}else{ //If not a file then treat as a folder
			size_t pos = location.find_last_of("/");
			if(pos != location.length()-1) location += "/";

			if(gameNo == 0){
				switch(fileType){
					case FULL:
						LOGSYSTEM->Log("Reading Location:"+location,1);
						//if Settlers 1
						if(Functions::FileExists(location + "SETTLER.BAT")){
							gameNo = 1;
						}
						//if Settlers 2
						else if((Functions::FolderExists(location + "s2"))||(Functions::FileExists(location + "s2.exe"))
								||(Functions::FileExists(location + "S2.EXE"))){
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
						break;

					case GFX:
					case SND:
					case MAP:
						gameNo = 3;
						break;

				}

			}
		}
//Make sure a Game Number has been selected
		if ((gameNo == 0)||(gameNo >= 5)){
			LOGSYSTEM->Error("Game Number Not found.ass");
			return false;
		}

		switch(fileType){
			case FULL:
				return FULLRAW(location,gameNo,GOG);
			case GFX:
			case SND:
			case MAP:{
				Settlers3::Extract* s3Extract = new Settlers3::Extract();
				if(s3Extract->ManualExtract(fileType, location) == false) return false;
				delete s3Extract;
				return false;
			}
			default:
				LOGSYSTEM->Error("UNKNOWN OPTION HOW DID THIS APPEAR?");
				return false;
		}


	return true;
	}

	bool FULLRAW(std::string location, char gameNo, bool GOG){

		switch(gameNo){
			case 1:{
				//temp message of version
				LOGSYSTEM->Log("Settlers 1 Detected.",1);
				LOGSYSTEM->Error("Settlers 1 not implemented yet.");
				return false;
			}
			case 2:{
				//temp message of version
				if(GOG)
					LOGSYSTEM->Log("Settlers 2 GOG Detected.",1);
				else
					LOGSYSTEM->Log("Settlers 2 Detected.",1);
				LOGSYSTEM->Error("Settlers 2 not implemented yet.");
				return false;
			}
			case 3:{
				Settlers3::Extract* s3Extract = new Settlers3::Extract(location,GOG);
				if(s3Extract->FullRAWExtract() == false) return false;
				delete s3Extract;
				return true;
			}
			case 4:{
				//temp message of version
				if(GOG)
					LOGSYSTEM->Log("Settlers 4 GOG Detected.",1);
				else
					LOGSYSTEM->Log("Settlers 4 Detected.",1);

				LOGSYSTEM->Error("Settlers 4 not implemented yet.");
				return false;
			}
			default:{
				// If nothing above found then
				LOGSYSTEM->Error("No game Detected.");
				return false;
			}
		}
	}
}

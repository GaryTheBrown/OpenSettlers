/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "StartupArguments.h"

StartupArguments::StartupArguments(int argc,char **argv) {
	this->argc = argc;
	this->argv = argv;
}
//Separate Functions because of requiring return!
bool StartupArguments::CheckArguments(ConfigList* configList){
	if(argc > 1){
		//First Argument Commands
		std::string argument = argv[1];
		std::transform(argument.begin(), argument.end(), argument.begin(), toupper);
		if (argument[0] == '-'){
			//CLI Converter
			if (argument == "-C"||argument == "--CONVERTER"){
				if(argc == 2){
					std::string fileName = argv[0];
					std::cout <<	PACKAGE_NAME << " - Open Source Game Engine for Settlers type games" << std::endl;
					std::cout << "CONVERTER MODE" << std::endl;
					std::cout <<	"Usage: " << fileName << "--(c)onverter  [Input File/Folder] [Output Folder]" << std::endl;
					std::cout << std::endl;
					return true;
				}
				this->converter = true;
				this->location = argv[2];
				if(argc >= 4){
					this->outputLocation = argv[3];
				}
				return false;
			}

			//CLI Extractor
			else if (argument == "-E"||argument == "--EXTRACTOR"){
				if(argc == 2){
					std::string fileName = argv[0];
					std::cout <<	PACKAGE_NAME << " - Open Source Game Engine for Settlers type games" << std::endl;
					std::cout << "EXTRACTOR MODE" << std::endl;
					std::cout <<	"Usage: " << fileName << "--(e)xtractor  [Input File/Folder] [Output Folder]" << std::endl;
					std::cout << std::endl;
					return true;
				}
				this->extractor = true;
				this->location = argv[2];
				if(argc >= 4){
					this->outputLocation = argv[3];
				}
				return false;
			}
/*
			//Game Editor
			else if (argument == "-G"||argument == "--GAMEEDITOR"){
				this->gameEditor = true;
			}
*/
			//Help Command
			else if (argument == "-H"||argument == "--HELP"){
				std::string fileName = argv[0];
				std::cout <<	PACKAGE_NAME << " - Open Source Game Engine for Settlers type games" << std::endl;
				std::cout <<	"Usage: " << fileName << " [FIRST OPTION] [OTHER OPTIONS]" << std::endl;
				std::cout <<	" [FIRST OPTION]" << std::endl;
				std::cout <<	"	-c, --converter		: CLI Converter Mode" << std::endl;
				std::cout <<	"	-e, --extractor		: CLI Extractor Mode" << std::endl;
//				std::cout <<	"	-g, --gameeditor	: Go Direct to the Game Editor" << std::endl;
				std::cout <<	"	-h, --help			: Display a brief help text and exit" << std::endl;
//				std::cout <<	"	-m, --mapeditor		: Go Direct to the Map editor" << std::endl;
				std::cout <<	"	-t, --test			: TESTING Stuff (create and display some info)" << std::endl;
				std::cout <<	"	-v, --version		: Display version information and exit" << std::endl;
				std::cout << std::endl;
				std::cout <<	" [OTHER OPTIONS]" << std::endl;
				std::cout <<	"	-f, --fullscreen	: Start in full screen" << std::endl;
				std::cout <<	"	-r, --resolution	: Window Resolution {Width Height}" << std::endl;
				std::cout <<	"	-s, --settlers		: Settlers Game Number [1-4]" << std::endl;
				std::cout <<	"	-w, --windowengine	: Sets the Engine Used [SDL2/OGL21]" << std::endl;
				std::cout << std::endl;
				return true;
			}
/*
			//Map Editor
			else if (argument == "-M"||argument == "--MAPEDITOR"){
				this->mapEditor = true;
			}
*/

			//Test Function
			else if (argument == "-T"||argument == "--TEST"){
				this->test = true;
				this->location = argv[2];
				return false;
			}
			//Version Info
			else if (argument == "-V"||argument == "--VERSION"){
				std::cout << PACKAGE_NAME << ": VERSION V" << PACKAGE_VERSION << std::endl;
				return true;
			}
		}
//Flags Read From Anywhere
		for(int i = 1;i < argc;i++){
			argument = argv[i];
			std::transform(argument.begin(), argument.end(), argument.begin(), toupper);
			if (argument[0] == '-'){
				//Fullscreen Toggle
				if (argument == "-F"||argument == "--FULLSCREEN"){
					configList->SetValue("fullscreen",true);
				//Game Number
				}else if (argument == "-S"||argument == "--SETTLERS"){
					try{
						this->gameNumber = atoi(argv[i+1]);
						i++;
					}
					catch(std::exception const & e){
						std::cout<< "Argument error : " << e.what() <<std::endl;
						return true;
					}
				}else if (argument == "-R"||argument == "--RESOLUTION"){
					try{
						std::pair<int,int> pair = std::make_pair(atoi(argv[i+1]),atoi(argv[i+2]));
						configList->SetValue("windowsize",pair);

//						this->windowSize.first = atoi(argv[i+1]);
//						this->windowSize.second = atoi(argv[i+2]);
						i++;
						i++;
					}
					catch(std::exception const & e){
						std::cout<< "Argument error : " << e.what() <<std::endl;
						return true;
					}
				//Window Engine
				}else if (argument == "-W"||argument == "--WINDOWENGINE"){
					try{
						std::string argument2 = argv[i+1];
						std::transform(argument2.begin(), argument2.end(), argument2.begin(), toupper);
						if (argument2 == "SDL2"){
							this->systemType = ST_SDL2;
						}else if (argument2 == "OGL21"){
							this->systemType = ST_OGL21;
						}else {
							LOGSYSTEM->Error("Window Engine Version Not Recognised Using Default: OpenGL 2.1");
						}
						i++;
					}
					catch(std::exception const & e){
						std::cout<< "Argument error : " << e.what() <<std::endl;
						return true;
					}
				}//else{
				//}
			}
		}
	}
	return false;
}


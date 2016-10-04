//============================================================================
// Name        : StartupArguments.cpp
// Author      : Gary_The_Brown
// Copyright   :
// Description :
//============================================================================
#include "StartupArguments.h"

StartupArguments::StartupArguments(int argc,char **argv) {
	this->argc = argc;
	this->argv = argv;
}
//Separate Functions because of requiring return!
bool StartupArguments::CheckArguments(){
	if(argc > 1){
//First Argument Commands
		std::string argument = argv[1];
		if (argument[0] == '-'){
			//Help Command
			if (argument == "-h"||argument == "--help"){
				std::cout <<	"OpenSettlers - Open Source Game Engine for Settlers type games" << std::endl;
				std::cout <<	"Usage: %s [FIRST OPTION] [OTHER OPTIONS]" << std::endl;
				std::cout <<	" [FIRST OPTION]" << std::endl;
				std::cout <<	"	-e, --extractor  : CLI Extractor Mode" << std::endl;
				std::cout <<	"	-g, --gameeditor : Go Direct to the Game Editor" << std::endl;
				std::cout <<	"	-h, --help       : Display a brief help text and exit" << std::endl;
				std::cout <<	"	-m, --mapeditor  : Go Direct to the Map editor [GAME] Required" << std::endl;
				std::cout <<	"	-t, --test       : TESTING Stuff (create and display some info)" << std::endl;
				std::cout <<	"	-v, --version    : Display version information and exit" << std::endl;
				std::cout << std::endl;
				std::cout <<	" [OTHER OPTIONS]" << std::endl;
				std::cout <<	"	-f, --fullscreen : Start in full screen" << std::endl;
				std::cout <<	"	-s, --settlers   : Settlers Game Number [1-4]" << std::endl;
				std::cout << std::endl;
				return true;
			}
			//Version Info
			else if (argument == "-v"||argument == "--version"){
				std::cout <<"GAME VERSION V" << VERSIONNUMBER << std::endl;
				return true;
			}
			//Test Function
			else if (argument == "-t"||argument == "--test"){
				this->test = true;
				return false;
			}
			//CLI Extractor
			else if (argument == "-e"||argument == "--extractor"){
				this->extractor = true;
				return false;
			}
/*
			//Game Editor
			else if (argument == "-g"||argument == "--gameeditor"){
				this->gameEditor = true;
			}
			//Map Editor
			else if (argument == "-m"||argument == "--mapeditor"){
				this->mapEditor = true;
			}
*/
		}
	}
	if(argc > 1){
//Flags Read From Anywhere
	//TODO ADD MORE OPTIONS FOR GAME NUMBER ETC.
		for(int i = 1;i < argc;i++){
			std::string argument = argv[i];
			if (argument[0] == '-'){
				//Fullscreen Toggle
				if (argument == "-f"||argument == "--fullscreen"){
					this->fullscreen = true;
				}else if (argument == "-s"||argument == "--settlers"){
					try{
						std::string argument2 = argv[i+1];
						this->gameNumber = std::stoi(argv[i+1]);
						i++;
					}
					catch(std::exception const & e){
						std::cout<< "Argument error : " << e.what() <<std::endl;
						return true;
					}
				}
			}
		}
	}
	return false;
}

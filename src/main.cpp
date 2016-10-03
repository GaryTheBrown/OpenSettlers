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
//temp version number until build system sorted
	std::string VERSION = "0.0 ALPHA";

	std::string ProgramName = argv[0];
	std::string option;
	if (argc > 1) option = argv[2];
	if(argc == 1){
		std::cout << "Open Settlers" << std::endl;

	} else if(argc == 2){
		if (option == "-v"){
			std::cout << "Open Settlers version " << VERSION << std::endl;
			std::cout << "USAGE:" << ProgramName << " [LOCATION/FILE]" << std::endl;
			return 0;
		} else {
			std::cout << "Unknown Options" << std::endl;
		}
	} else if(argc == 3){

		if (option == "-e"){
			LOGSYSTEM->Log("Settlers Extractor Started",1);
			if (Extractor::Main(argv[2]) == false) return 0;
			LOGSYSTEM->Log("Settlers Extractor Completed",1);
			return 0;
		} else {
			std::cout << "Unknown Options" << std::endl;
		}
	} else {
		std::cout << "Unknown Options" << std::endl;
	}

	return 0;
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "main.h"
using namespace Extractor;
int main(int argc,char* argv[]) {
//temp version number until build system sorted
	std::string VERSION = "0.01";

	std::string ProgramName = argv[0];

	if(argc == 2){
		LOGSYSTEM->Log("Settlers Extractor Started",1);
		if (Main(argv[1],FULL,0) == false) return 0;
		LOGSYSTEM->Log("Settlers Extractor Completed",1);
		return 0;
	}else if(argc == 3){
		LOGSYSTEM->Log("Settlers Extractor Started",1);
		std::string type = argv[1];
		eType option;
		if(type == "FULL"){
			option = FULL;
		}else if(type == "GFX"){
			option = GFX;
		}else if(type == "SND"){
			option = SND;
		}else if(type == "MAP"){
			option = MAP;
		}
		Main(argv[2],option,0);
		LOGSYSTEM->Log("Settlers Extractor Completed",1);
		return 0;
	}
	std::cout << "Settlers Extractor version " << VERSION << std::endl;
	std::cout << "USAGE:" << std::endl;
	std::cout << ProgramName << " [LOCATION] To extract the full game data files" << std::endl;
	std::cout << ProgramName << " [FILE] To extract a single File" << std::endl;
	std::cout << ProgramName << " [OPTION] [LOCATION] To extract selected files from a Folder" << std::endl;
	std::cout << "OPTION: " << std::endl;
	std::cout << "		FULL =	Extract all GFX/SND Files" << std::endl;
	std::cout << "		GFX  =	Extract Settlers 3 GFX File" << std::endl;
	std::cout << "		SND  =	Extract Settlers 3 SND File" << std::endl;
	std::cout << "		MAP  =	Extract Settlers 3 MAP File" << std::endl;

	return 0;
}

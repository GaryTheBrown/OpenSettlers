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

int main(int argc,char* argv[]) {

	std::string ProgramName = argv[0];
	if(argc == 2){
		LOGSYSTEM->Log("Settlers Extractor Started",1);

		if (Extractor::Main(argv[1]) == false) return 0;
		LOGSYSTEM->Log("Settlers Extractor Completed",1);
		return 0;
	}
	LOGSYSTEM->Message("USAGE: " + ProgramName + " [LOCATION]");

	return 0;
}

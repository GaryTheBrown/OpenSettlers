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

	//CLI Extractor
	if(startupArguments->Extractor()){
		LOGSYSTEM->Log("Settlers Extractor Started",1);
		if (Extractor::Main(startupArguments->Location()) == false) return 0;
		LOGSYSTEM->Log("Settlers Extractor Completed",1);
		return 0;
	}

	return 0;
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_FUNCTIONS_FILERUN_H_
#define EXTRACTOR_FUNCTIONS_FILERUN_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "../Log.h"

namespace Functions{
	class ExternalProgram {
	private:
		std::string location;
		std::string innoextract = "/usr/bin/innoextract";
		std::string innoextractArgumentsExtract = "-p 0 -c 0";
		std::string innoextractArgumentsGameCheck = "-c 0 --gog-game-id";
		std::string unshield = "/usr/bin/unshield";
		std::string unshieldArguments = "-g EXE x";
	public:

		ExternalProgram(std::string location){this->location = location;};
		virtual ~ExternalProgram(){};
		std::string Run(std::string program, std::string arguments, bool show = true);
		bool GOGExtract();
		std::string GOGGameCheck();
		bool CABExtract(std::string file);
	};
}
#endif

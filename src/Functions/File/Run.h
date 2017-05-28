/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "../../Log.h"

namespace Functions{
	class ExternalProgram{
	private:
		std::string location;
		std::string innoextract = "/usr/bin/innoextract";
		std::string innoextractArgumentsExtract = "-p 0 -c 0";
		std::string innoextractArgumentsGameCheck = "-c 0 --gog-game-id";
		std::string unshield = "/usr/bin/unshield";
		std::string unshieldArguments = "-g EXE x";
	public:

		explicit ExternalProgram(std::string location):location(location){};
		~ExternalProgram(){};
		std::string Run(std::string program, std::string arguments, bool show = true);
		bool GOGExtract();
		std::string GOGGameCheck();
		bool CABExtract(std::string file);
	};
}

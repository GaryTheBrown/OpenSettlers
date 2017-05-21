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

#include <iostream>
#include <string>
#include <algorithm>

#include "Log.h"
#include "config.h"

class StartupArguments {
public:
	enum SystemType : char{
		ST_SDL2,
		ST_OGL21
	};

private:

	int argc;
	char **argv;

	//Options
	bool converter = false;
	bool extractor = false;
	bool fullscreen = false;
	bool gameEditor = false;
	bool mapEditor = false;
	bool test = false;

	int gameNumber = 0;
	SystemType systemType = ST_OGL21;
	std::string location = "";
	std::string configLocation = "";
	std::pair<int,int> windowSize = std::make_pair(800,600);

public:
	StartupArguments(int argc,char **argv);
	virtual ~StartupArguments(){};

	bool CheckArguments();

	//Getters
	bool Converter(){return this->converter;}
	bool Extractor(){return this->extractor;}
	bool Fullscreen(){return this->fullscreen;}
	bool GameEditor(){return this->gameEditor;}
	bool MapEditor(){return this->mapEditor;}
	bool Test(){return this->test;}

	int GameNumber(){return this->gameNumber;}
	SystemType SystemType(){return this->systemType;}
	std::string Location(){return this->location;}
	std::string ConfigLocation(){return this->configLocation;}
	std::pair<int,int> WindowSize(){return this->windowSize;};
};

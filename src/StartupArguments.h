//============================================================================
// Name        : StartupArguments.h
// Author      : Gary_The_Brown
// Copyright   :
// Description :
//============================================================================

#pragma once

#include <iostream>
#include <string>
#include "global.h"

class StartupArguments {
private:

	int argc;
	char **argv;

	//Options
	bool test = false;
	bool fullscreen = false;
	bool extractor = false;
	bool gameEditor = false;
	bool mapEditor = false;

	int gameNumber = 0;

	std::string location = "";

public:
	StartupArguments(int argc,char **argv);
	virtual ~StartupArguments(){};

	bool CheckArguments();

	//Getters
	bool Test(){return this->test;}
	bool Fullscreen(){return this->fullscreen;}
	bool Extractor(){return this->extractor;}
	bool GameEditor(){return this->gameEditor;}
	bool MapEditor(){return this->mapEditor;}

	int GameNumber(){return this->gameNumber;}

	std::string Location(){return this->location;}

};

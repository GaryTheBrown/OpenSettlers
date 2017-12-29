/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef RETURNDATA_H
#define RETURNDATA_H

#include <string>
#include <vector>
#include "MenuEvents.h"
#include "Functions/To.h"
#include "Functions/File/DataReader.h"

class ReturnData {
private:
	eMenuEvent rMenuEvent = MMNothing;
	unsigned int rInt = 0;
	std::string rString = "";

public:
	ReturnData();
	ReturnData(eMenuEvent rMenuEvent);
	ReturnData(eMenuEvent rMenuEvent, std::string rString);
	ReturnData(eMenuEvent rMenuEvent,unsigned int rInt);
	ReturnData(eMenuEvent rMenuEvent,unsigned int rInt , std::string rString);

	explicit ReturnData(Functions::DataReader* reader);

	virtual ~ReturnData(){};

	const eMenuEvent MenuEvent(){return this->rMenuEvent;}
	const unsigned int Int(){return this->rInt;}
	const std::string String(){return this->rString;}

	void MenuEvent(eMenuEvent rMenuEvent){this->rMenuEvent = rMenuEvent;}
	void Int(unsigned int rInt){this->rInt = rInt;}
	void String(std::string *rString){this->rString = *rString;}

	bool ToSaveToData(std::vector<char>* data = NULL);
	std::string ToString();

	//Search and sort functions
    bool operator != (const ReturnData& str) const {return (this->rMenuEvent != str.rMenuEvent);};
    bool operator == (const ReturnData& str) const {return (this->rMenuEvent == str.rMenuEvent);};
};

#endif
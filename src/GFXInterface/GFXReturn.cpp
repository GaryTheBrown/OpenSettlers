/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GFXReturn.h"

GFXInterface::GFXReturn::GFXReturn(eMenuEvent rMenuEvent) {
	this->rMenuEvent = rMenuEvent;
}

GFXInterface::GFXReturn::GFXReturn(eMenuEvent rMenuEvent, std::string rString) {
	this->rMenuEvent = rMenuEvent;
	this->rString = rString;
}

GFXInterface::GFXReturn::GFXReturn(eMenuEvent rMenuEvent,int returnInt){
	this->rMenuEvent = rMenuEvent;
	this->rInt = returnInt;
}

GFXInterface::GFXReturn::GFXReturn(eMenuEvent rMenuEvent,int returnInt , std::string rString){
	this->rMenuEvent = rMenuEvent;
	this->rInt = returnInt;
	this->rString = rString;
}




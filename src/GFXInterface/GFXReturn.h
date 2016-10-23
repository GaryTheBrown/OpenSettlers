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
#include "../MenuEvents.h"

namespace GFXInterface {
	class GFXReturn {
	private:
		eMenuEvent rMenuEvent = MMNothing;
		int rInt = 0;
		std::string rString = "";
	public:
		GFXReturn();
		GFXReturn(eMenuEvent rMenuEvent);
		GFXReturn(eMenuEvent rMenuEvent, std::string rString);
		GFXReturn(eMenuEvent rMenuEvent,int rInt);
		GFXReturn(eMenuEvent rMenuEvent,int rInt , std::string rString);
		//GUIReturn(int returnInt);
		//GUIReturn(std::string returnString);

		virtual ~GFXReturn(){};

		eMenuEvent MenuEvent(){return this->rMenuEvent;}
		int Int(){return this->rInt;}
		std::string String(){return this->rString;}

		void MenuEvent(eMenuEvent rMenuEvent){this->rMenuEvent = rMenuEvent;}
		void Int(int rInt){this->rInt = rInt;}
		void String(std::string rString){this->rString = rString;}
	};
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#include "../../../Functions/Image/RGBA.h"
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/File/TextLoad.h"
#include "../../APILEVELS.h"
#include "../FileTypes.h"
#include "../../../Log.h"

#include "GUIItems/GUIImageData.h"
#include "GUIItems/GUIButtonData.h"
#include "GUIItems/GUITextData.h"
#include "GUIItems/GUIBoxData.h"

namespace OSData{
	class MenuLayout : public FileTypes{
	private:
		bool fileOK = true;

		unsigned int APIVersion = APILEVEL::MENULAYOUT;
		int menuID = 0;
		std::string title;
		RGBA backgroundColour;

	public:
		std::vector<GUIItemData*>* itemData = NULL;

		//constructors
		MenuLayout(int menuID,std::string title,RGBA backgroundColour,std::vector<GUIItemData*>* itemData);
		MenuLayout(Functions::DataReader* reader);
		MenuLayout(std::string file);
		virtual ~MenuLayout();

		//getters
		int MenuID(){return menuID;}
		std::string Title(){return title;}
		RGBA BackgroundColour(){return backgroundColour;}

		//functions

		bool ToSaveToData(std::vector<char>* data = NULL);

	};
}

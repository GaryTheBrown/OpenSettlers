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
#include <vector>
#include <utility>
#include <algorithm>
#include <libxml/tree.h>

#include "../../../Functions/Image/RGBA.h"
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/To.h"
#include "../../../Log.h"
#include "../../APILEVELS.h"
#include "../FileTypes.h"
#include "GUIItems/GUIImageData.h"
#include "GUIItems/GUIButtonData.h"
#include "GUIItems/GUITextData.h"
#include "GUIItems/GUIBoxData.h"
#include "GUIItems/GUIItemNew.h"

namespace OSData{
	class MenuLayout : public FileTypes {
	private:

		unsigned int APIVersion = APILEVEL::MENULAYOUT;
		int menuID = 0;
		std::string title;
		RGBA backgroundColour;
		std::vector<GUIItemData*>* itemData = NULL;

	public:


		MenuLayout(int menuID,std::string title,RGBA backgroundColour,std::vector<GUIItemData*>* itemData);
		MenuLayout(Functions::DataReader* reader);
		MenuLayout(xmlNode* node);

		virtual ~MenuLayout();

		int MenuID(){return menuID;}
		std::string Title(){return title;}
		RGBA BackgroundColour(){return backgroundColour;}
		std::vector<GUIItemData*>* ItemData(){return this->itemData;};

		bool ToSaveToData(std::vector<char>* data = NULL);
		bool ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations = NULL);
		bool LinkNumbers(std::vector<Functions::RGBImage*>* images);
		std::string ToString();

	    bool operator < (const MenuLayout& str) const {return (menuID < str.menuID);};
	};
}

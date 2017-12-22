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
		unsigned int menuID = 0;
		std::string title;
		RGBA backgroundColour;
		std::vector<GUIItemData*>* itemData = NULL;

		void CheckValues(std::string name, std::string value);
	public:


		MenuLayout(unsigned int menuID,std::string title,RGBA backgroundColour,std::vector<GUIItemData*>* itemData);
		explicit MenuLayout(Functions::DataReader* reader);
		explicit MenuLayout(xmlNode* node);

		virtual ~MenuLayout();

		const unsigned int MenuID(){return menuID;}
		const std::string Title(){return title;}
		const RGBA BackgroundColour(){return backgroundColour;}
		std::vector<GUIItemData*>* ItemData(){return this->itemData;};

		bool ToSaveToData(std::vector<char>* data = NULL);
		bool ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations = NULL);
		bool LinkNumbers(std::vector<Functions::RGBImage*>* images);
		std::string ToString();

		//Search and sort functions
	    bool operator < (const MenuLayout& str) const {return (this->menuID < str.menuID);};

	};
}

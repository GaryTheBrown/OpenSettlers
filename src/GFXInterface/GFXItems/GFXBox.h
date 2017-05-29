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
#include <stdio.h>
#include <vector>
#include <utility>

#include "../../ConfigList.h"
#include "../../MenuEvents.h"
#include "../../Functions/To.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/GUIBoxData.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/GUIItemData.h"
#include "../../OSDataFile/FileTypes/GameData.h"
#include "GFXButton.h"
#include "GFXImage.h"
#include "GFXSpacer.h"
#include "GFXItem.h"
#include "../../ReturnData.h"


namespace GFXInterface {
	class GFXBox : public GFXItem{
	private:
		OSData::GUIBoxData* boxData;
		RGBA backgroundColour;
		OSData::GUIBoxData::eBoxType boxType;
		bool multiSelect;
		std::vector<GFXItem*>* itemList;
		GFXButton* selected;

	public:

		GFXBox(SystemInterface::System* system, ConfigList* configList, OSData::GUIBoxData* BoxData, OSData::GameAddons addons);
		virtual ~GFXBox();

		//getters
		bool GetMultiSelect(){return this->multiSelect;}
		GFXItem* GetSelected(){return this->selected;}

		//functions
		void CalculateItems();
		void Draw();
		void CalculateLocation(std::pair<int,int> location = {0,0},std::pair<int,int> windowSize = {0,0});
		ReturnData EventHandler();

	};
}


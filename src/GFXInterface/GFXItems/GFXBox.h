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

#include "../../MenuEvents.h"
#include "../../Functions/To.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/GUIBoxData.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/GUIItemData.h"
#include "GFXButton.h"
#include "GFXImage.h"
#include "GFXItem.h"
#include "../GFXReturn.h"


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

		GFXBox(SystemInterface::System* system,OSData::GUIBoxData* BoxData);
		virtual ~GFXBox();

		//getters
		bool GetMultiSelect(){return this->multiSelect;}
		virtual GFXItem* GetSelected(){return this->selected;}

		//functions
		void CalculateItems();
		virtual void Draw();
		virtual void CalculateLocation(OSData::GUIItemData* data);
		virtual eMenuEvent EventHandler();

	};
}


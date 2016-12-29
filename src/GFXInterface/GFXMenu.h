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
#include "../MenuEvents.h"
#include "../Functions/Image/RGBA.h"
#include "../SystemInterface/System.h"
#include "../OSDataFile/FileTypes/Layout/MenuLayout.h"
#include "../OSDataFile/FileTypes/GameData.h"
#include "GFXItems/GFXBox.h"
#include "GFXItems/GFXButton.h"
#include "GFXItems/GFXImage.h"
#include "GFXItems/GFXText.h"
#include "GFXItems/GFXSpacer.h"
#include "../ReturnData.h"

namespace GFXInterface {
	class GFXMenu {
	protected:
		SystemInterface::System* system;
		OSData::MenuLayout* menuLayout;
		std::string title;
		RGBA backgroundColour;
		std::vector<GFXItem*>* itemList = NULL;

	public:
		GFXMenu(SystemInterface::System* system, OSData::MenuLayout* menuLayout, OSData::GameAddons addons);
		virtual ~GFXMenu();

		std::string Title(){return title;}

		void Draw();
		void ResizedWindow();

		virtual ReturnData Loop();
		virtual ReturnData EventHandler();

	};
}

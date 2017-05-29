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
#include "../ConfigList.h"
#include "../SystemInterface/System.h"
#include "../OSDataFile/FileTypes/GameType.h"
#include "../OSDataFile/FileTypes/GameData.h"
#include "../GFXInterface/GFXMenu.h"
#include "../ReturnData.h"
#include "../OSDataFile/FileTypes/Layout/MenuLayout.h"

namespace GameInterface {
	class GameMenu {
	private:
		SystemInterface::System* system;
		ConfigList* configList;
		std::vector<OSData::MenuLayout*>* menuLayouts;
		unsigned int startMenuNumber;
		GFXInterface::GFXMenu* menu;
		OSData::GameAddons addons;
	public:
		GameMenu(SystemInterface::System* system, ConfigList* configList, std::vector<OSData::MenuLayout*>* menuLayouts, unsigned int startMenuNumber, OSData::GameAddons addons);
		virtual ~GameMenu();

		ReturnData Loop();
	};
}

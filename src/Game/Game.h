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

#include "../SystemInterface/System.h"
#include "../OSDataFile/FileTypes/GameType.h"
#include "../GFXInterface/GFXMenu.h"
#include "../ReturnData.h"
#include "../OSDataFile/FileTypes/Layout/MenuLayout.h"

#include "GameMenu.h"

namespace GameInterface {
	class Game {
	private:
		SystemInterface::System* system;
		OSData::GameType* gameType;
		GameMenu* menu;
	public:
		Game(SystemInterface::System* system,OSData::GameType* gameType, signed int startMenuNumberOverride = -1);
		virtual ~Game();

		ReturnData Loop();
	};
}

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

#include <algorithm>
#include <string>
#include <sstream>
#include <type_traits>

namespace OSData {
	//All Settlers Addons (Not needed yet but will be used later on)

	enum GameAddons: unsigned char{
		eS1None = 0,

		eS2None = 0,
		eS2MissionCD = 1,
		eS2Gold = 2,

		eS3None = 0,
		eS3MissionCD = 1,
		eS3Amazon = 2,
		eS3Gold = 4,

		eS4None = 0,
		eS4MissionCD = 1,
		eS4Trojan = 2,
		eS4Gold = 4,
		eS4NewWorld = 8,
		eS4Community = 16
	};

	extern GameAddons AddonDataFromText(std::string text);
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef GFXINTERFACE_GFXLOADINGSCREEN_H
#define GFXINTERFACE_GFXLOADINGSCREEN_H

#include <string>
#include <vector>
#include "../ConfigList.h"
#include "../MenuEvents.h"
#include "../Functions/Image/RGBA.h"
#include "../SystemInterface/System.h"
#include "../OSDataFile/FileTypes/Layout/LoadingScreenLayout.h"
#include "../OSDataFile/FileTypes/GameData.h"
#include "GFXItems/GFXImage.h"
#include "../ReturnData.h"

namespace GFXInterface {
	class GFXLoadingScreen {
	protected:
		SystemInterface::System* system;
		ConfigList* configList;
		OSData::LoadingScreenLayout* loadingScreenLayout;
		std::string title;
		RGBA backgroundColour;
		std::vector<GFXImage*>* imageList = NULL;

	public:
		GFXLoadingScreen(SystemInterface::System* system, ConfigList* configList, OSData::LoadingScreenLayout* loadingScreenLayout, OSData::GameAddons addons);
		virtual ~GFXLoadingScreen();

		std::string Title(){return title;}

		void Draw();
		void ResizedWindow();

		//ReturnData Loop();
		//ReturnData EventHandler();

	};
}

#endif
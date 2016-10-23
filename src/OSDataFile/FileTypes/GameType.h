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

#include "FileTypes.h"

#include "../../Functions/File/DataReader.h"
#include "../../Log.h"

#include "Layout/MenuLayout.h"

//#include "GameOptions.h"
//#include "Layout.h"
//#include "MapSetup.h"
//#include "Resource.h"
//#include "Race.h"
//#include "Building.h"
//#include "../Functions/LoadFunctions.h"

namespace OSData {
	class GameType : public FileTypes {
	private:
	//TODO: ADD IN VARIABLE MAYBE FLOAT TO GET VERSION FROM.
		std::string gameName;
		//std::string baseGame; 	//TODO Look into this base game option to allow people to add to a base game rather than have to download all base graphics too (could be illegal?)
		//bool hasGameIcon; //location relative to "game"/GFX/ = icon.png

		std::vector<MenuLayout*>* menuLayouts = NULL;
		//GameOptions* gameOptions;
		//Layout* layout;
		//List<Race>* raceList;
		//List<Resource>* resourceList;
		//MapSetup* mapSetup;

		void CheckValues(std::string name, std::string value);
		void GetFileType(std::string data);
		void DoFileType(void* data, bool xml = false);
	public:


		GameType();
		GameType(std::string gameName,
			std::vector<MenuLayout*>* menuLayouts
	//			GameOptions* gameOptions,
	//			Layout* layout,
	//			MapSetup* mapSetup,
	//			std::vector<Resource*>* resourceList,
	//			std::vector<Race*>* raceList
				 );

		GameType(Functions::DataReader* reader);
		GameType(xmlNode* node);

		virtual ~GameType();

		std::string GameName(){return this->gameName;}
		std::vector<MenuLayout*>* MenuLayouts(){return this->menuLayouts;};
		//GameOptions* GameOptions;
		//Layout* Layout;
		//List<Race>* RaceList;
		//List<Resource>* ResourceList;
		//MapSetup* MapSetup;

		std::string ToString();

	};
}

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
	//TODO ADD IN VARIABLE MAYBE FLOAT TO GET VERSION FROM.
		std::string gameName = "";
		unsigned int startMenuNumber = 0;
		//std::string baseGame; 	//TODO Look into this base game option to allow people to add to a base game rather than have to download all base graphics too (could be illegal?)
		//bool hasGameIcon;
		std::vector<MenuLayout*>* menuLayouts = NULL;
		//GameOptions* gameOptions;
		//List<Race>* raceList;
		//List<Resource>* resourceList;
		//MapSetup* mapSetup;

		void CheckValues(std::string name, std::string value);
		FileTypes::eFileType GetFileType(std::string data);
		void DoFileType(FileTypes::eFileType fileType, void* data, bool xml = false);
	public:


		GameType();
		GameType(std::string gameName, unsigned int startMenuNumber = 0);
		GameType(std::string gameName, unsigned int startMenuNumber, std::vector<MenuLayout*>* menuLayouts
	//			GameOptions* gameOptions,
	//			MapSetup* mapSetup,
	//			std::vector<Resource*>* resourceList,
	//			std::vector<Race*>* raceList
				 );

		GameType(Functions::DataReader* reader);
		GameType(xmlNode* node);

		virtual ~GameType();

		void StartMenuNumber(unsigned int startMenuNumber){this->startMenuNumber = startMenuNumber;};
		void AddMenuLayout(MenuLayout* menuLayout){this->menuLayouts->push_back(menuLayout);}

		std::string GameName(){return this->gameName;}
		unsigned int StartMenuNumber(){return this->startMenuNumber;}
		std::vector<MenuLayout*>* MenuLayouts(){return this->menuLayouts;};

		bool ToSaveToData(std::vector<char>* data);
		bool ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations = NULL);
		bool LinkNumbers(std::vector<Functions::RGBImage*>* images);
		std::string ToString();

	};
}

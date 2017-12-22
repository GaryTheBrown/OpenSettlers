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
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <libxml/tree.h>

#include "../GameData.h"
#include "../FileTypes.h"
#include "../../../Functions/File/DataReader.h"
#include "../../../Log.h"

namespace OSData {
	class MapSetup : public FileTypes {
	private:
		//Plane128x128
		//Plane32x32
		//Hexagon
		//OTHER ODD SHAPE
		//std::vector<TerrainData*>* terrainData = NULL;

		void CheckValues(std::string name, std::string value);
		void DoFileType(FileTypes::eFileType fileType, void* data);
	public:
		MapSetup();
		explicit MapSetup(Functions::DataReader* reader);
		explicit MapSetup(xmlNode* node);

		virtual ~MapSetup();
	};
}

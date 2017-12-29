/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/


// http://settlers2.net/documentation/world-map-file-format-wldswd/
#ifndef EXTRACTOR_SETTLERS2_MAP_MAPDATATYPE_H
#define EXTRACTOR_SETTLERS2_MAP_MAPDATATYPE_H
#include <string>
#include <vector>

#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/File/Functions.h"
#include "../../../Functions/To.h"
#include "../../../Log.h"
#include "MAPHeader.h"
#include "MAPBlock.h"

namespace Extractor{
	namespace Settlers2{
		class MAPDataType{
		private:

			MAPHeader* header;

//TODO RENAME THESE AS ADDED
			MAPBlock* block1;  //Height map
			MAPBlock* block2;  //Texture triangle #1 ▲
			MAPBlock* block3;  //Texture triangle #2 ▼
			MAPBlock* block4;  //Roads
			MAPBlock* block5;  //Object Index
			MAPBlock* block6;  //Object Type
			MAPBlock* block7;  //Animals
			MAPBlock* block8;  //Unknown / Internal? / Savegame?
			MAPBlock* block9;  //Buildable sites
			MAPBlock* block10; //Unknown / Internal? / Savegame? all 7s
			MAPBlock* block11; //Map Editor cursor position
			MAPBlock* block12; //Resources
			MAPBlock* block13; //Gouraud Shading
			MAPBlock* block14; //Passable Areas
			MAPBlock* footer;

		public:
			explicit MAPDataType(std::string file);
			~MAPDataType();

			void SaveToFile(std::string location);
		};
	}
}

#endif
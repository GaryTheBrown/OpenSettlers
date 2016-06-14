/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPAREA_H_
#define EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPAREA_H_

#include <string>
#include "../../../../Log.h"
#include "../../../../LogSystem/LogSystem.h"
#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/FileSave.h"
#include "../../../../Functions/To.h"
#include "../MAPParts.h"

namespace Extractor{
	namespace Settlers3{
		class MAPArea: public MAPParts{
		public:
			struct MapTile{
				unsigned char height = 0;
				unsigned char type = 0;
				unsigned char object = 0; // Connected to MapObjects.h
				unsigned char playerClaim = 0;// -1 = NONE
				unsigned char accessible = 0;// 0 = YES 1 = NO
				unsigned char resources = 0; //Connected to Resources.h
			};
		private:
			//Map Info
			int mapSizeHeight = 0;
			int mapSizeWidth = 0;
			MapTile* mapData = NULL;

		public:
			MAPArea(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey);
			virtual ~MAPArea();
			virtual std::string HeaderToString();
			void SaveFileData(std::string location);


			int MapSizeHeight(){return this->mapSizeHeight;};
			int MapSizeWidth(){return this->mapSizeWidth;};
			MapTile* MapData(){return this->mapData;}
		};
	}
}
#endif

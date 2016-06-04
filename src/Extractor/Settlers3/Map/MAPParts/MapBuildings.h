/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPBUILDINGS_H_
#define EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPBUILDINGS_H_

#include <string>
#include "../../../../Log.h"
#include "../../../../LogSystem/LogSystem.h"
#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/FileSave.h"
#include "../../../../Functions/To.h"
#include "../../../../Functions/OutputVar.h"
#include "../MAPParts.h"
#include "../../Lists/Buildings.h"

namespace Extractor{
	namespace Settlers3{
		class MAPBuildings: public MAPParts{
		public:
			struct Building{
				char player;
				char type;
				short x_pos;
				short y_pos; //(-1?)
				char unknown1; //AAAA BBBB
				char unknown2; //AAAA BBBB A = L1 Sword	B = L2 Sword
				char unknown3; //AAAA BBBB A = L2 Bow	B = L3 Bow
				char unknown4; //AAAA BBBB A = L3 Sword	B = L1 Bow
				char unknown5; //AAAA BBBB A = L3 Spear B = UNKNOWN
				char unknown6; //AAAA BBBB A = L1 Spear	B = L2 Spear
			};
		private:
			unsigned int buildingCount;
			Building* buildings;
		public:
			MAPBuildings(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey);
			virtual ~MAPBuildings();
			virtual std::string HeaderToString();
			void SaveFileData(std::string location);
		};
	}
}
#endif


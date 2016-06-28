/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <string>
#include "../../../../Log.h"
#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/File/Save.h"
#include "../../../../Functions/To.h"
#include "../MAPParts.h"
#include "../../Lists/Buildings.h"

namespace Extractor{
	namespace Settlers3{
		class MAPBuildings : public MAPParts{
		public:

			struct Building{
				char player;
				char type;
				short x_pos;
				short y_pos;

				struct Soldiers{
					char unknown = 0;
					char sword1 = 0;
					char sword2 = 0;
					char sword3 = 0;
					char bow1 = 0;
					char bow2 = 0;
					char bow3 = 0;
					char spear1 = 0;
					char spear2 = 0;
					char spear3 = 0;
				} soldiers;
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

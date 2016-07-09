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
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/To.h"
#include "../MAPParts.h"

namespace Extractor{
	namespace Settlers3{
		class MAPPlayerInfo : public MAPParts{
		public:
			struct PlayerInfo{
				unsigned int armyType;//(00 = Roman 1 = Egyptian 2 = Asian(JAP) 3 = Amazon)
				unsigned int locationX;
				unsigned int locationY;
				std::string name;
			};

		private:
			PlayerInfo* playerInfo;
			unsigned int playerCount;
		public:
			MAPPlayerInfo(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey, unsigned int playerCount);
			virtual ~MAPPlayerInfo(){delete [] this->playerInfo;};
			virtual std::string ToString();
		};
	}
}

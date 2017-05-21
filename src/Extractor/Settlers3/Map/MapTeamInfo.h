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
#include "../../../Log.h"
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/To.h"
#include "MAPParts.h"
namespace Extractor{
	namespace Settlers3{
		class MAPTeamInfo : public MAPParts{
		public:
			enum enumControlType{
				ControlType_Choose = 0,
				ControlType_Human = 1,
				ControlType_Computer = 2
			};

			struct PlayerInfo{
				unsigned int Team;
				enumControlType controlType;
			};

		private:
			PlayerInfo* playerInfo;
			unsigned int playerCount;

		public:
			MAPTeamInfo(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey, unsigned int playerCount);
			virtual ~MAPTeamInfo(){delete [] this->playerInfo;};
			virtual std::string ToString();
		};
	}
}

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
#include "../../../Log.h"
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/To.h"
#include "MAPParts.h"
#include "MAPParts/MapInfo.h"
#include "MAPParts/MapArea.h"
#include "MAPParts/MapPreviewImage.h"
#include "MAPParts/MapPlayerInfo.h"
#include "MAPParts/MapText.h"
#include "MAPParts/MapTeamInfo.h"
#include "MAPParts/MapVictoryConditions.h"
#include "MAPParts/MapBuildings.h"
#include "MAPParts/MapSettlers.h"
#include "MAPParts/MapGoods.h"

namespace Extractor{
	namespace Settlers3{
		class MAPHeader{
		private:

			enum enumFileVersion{
				FILE_VERSION_NONE = 0x00,
				FILE_VERSION_DEFAULT = 0x0A,
				FILE_VERSION_AMAZONS = 0x0B
			};

			enum enumFileParts{
				PART_TYPE_EOF = 0, // End of File and Padding
				PART_TYPE_MapInfo = 1,
				PART_TYPE_PlayerInfo = 2,
				PART_TYPE_TeamInfo = 3,
				PART_TYPE_PreviewImage = 4,
				PART_TYPE_Area = 6,
				PART_TYPE_Settlers = 7,
				PART_TYPE_Buildings = 8,
				PART_TYPE_Resources = 9,
				PART_TYPE_VictoryConditions = 10,
				PART_TYPE_QuestText = 11,
				PART_TYPE_QuestTip = 12
			};

			//Header
			unsigned int fileChecksum;     //- @offset:00(4) check from 08 to end
			unsigned int fileVersion; //- @offset:04(4) NO_S3_FILE = 0x00, DEFAULT = 0x0A, AMAZONS = 0x0B

			MAPInfo* mapInfo = NULL;
			MAPArea* area = NULL;
			MAPPreviewImage* preview = NULL;
			MAPPlayerInfo* playerInfo = NULL;
			MAPTeamInfo* teamInfo = NULL;
			MAPSettlers* settlers = NULL;
			MAPBuildings* buildings = NULL;
			MAPGoods* goods = NULL;
			MAPVictoryConditions* victoryConditions = NULL;
			MAPText* questText = NULL;
			MAPText* questTip = NULL;

			//Checks
			bool goodChecksum;

			//Functions
			bool CheckChecksum(Functions::DataReader * reader);
		public:


			MAPHeader(Functions::DataReader* reader);
			~MAPHeader();

			std::string HeaderToString();
			void SaveFileData(std::string location);
		};
	}
}

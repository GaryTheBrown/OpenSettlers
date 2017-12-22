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
		class MAPInfo : public MAPParts{
		public:
			enum enumStartResources{
				startResourceLow = 1,
				startResourcesNormal = 2,
				startResourcesHigh = 3
			};

		private:

			//Map Info
			bool isSinglePlayerMap = true; //offset:00(4)
			int playerCount = 0; //offset:04(4)
			enumStartResources startResources = startResourcesNormal; //offset:08(4)
			//offset:12 to 24 EMPTY (Always Zero)


		public:
			MAPInfo(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey);
			virtual std::string ToString();
			const bool IsSinglePlayerMap(){return this->isSinglePlayerMap;};
			const int PlayerCount(){return this->playerCount;};
			const enumStartResources StartResources(){return this->startResources;};
		};
	}
}

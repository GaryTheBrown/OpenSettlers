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
#pragma once
#include <string>
#include <vector>

#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/File/Functions.h"
#include "../../../Functions/To.h"
#include "../../../Log.h"

namespace Extractor{
	namespace Settlers2{
		class MAPBlock{
		private:
			struct BlockHeader{ //  https://github.com/Return-To-The-Roots/libsiedler2/blob/master/src/ArchivItem_Map.cpp Line:77
				unsigned short id;// Must be 0x2710
				unsigned int unknown;// Always 0
				unsigned short width;
				unsigned short height;
				unsigned short multiplier;// Not sure, always 1
				unsigned int blockLength;
			} blockHeader;

		public:
			MAPBlock(Functions::DataReader* reader);
			~MAPBlock();

			void SaveToFile(std::string location);
		};
	}
}

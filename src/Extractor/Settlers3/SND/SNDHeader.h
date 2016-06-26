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
#include "../../../Functions/DataReader.h"
#include "../../../Functions/To.h"
#include "SNDFrame.h"

namespace Extractor{
	namespace Settlers3{
		class SNDHeader{
		private:
			//File Header
			unsigned int fileID;		//- @offset:00(4) File ID - 0x00011544 - 70980
			unsigned int version;		//- @offset:04(4) Version - 0x02 - 2
			unsigned int spacer;		//- @offset:08(4) - 0
			unsigned int headerSizeA;	//- @offset:12(4) - 0x1c - 28
			unsigned int fileSize;		//- @offset:16(4) -
			unsigned int unknown20;		//- @offset:20(4) - (00)-1 or (01)1
			unsigned int headerSizeB;	//- @offset:24(4) - 0x1c - 28

			//Sound Frames Default Header
			unsigned int headerID;		//- @offset:28(4) - (73588)
			unsigned short unknown32;	//- @offset:32(2) - (00) 484 (01) 12 //Total files?
			unsigned short count;		//- @offset:34(2) - (00) 119 (01) 1.

			//Frames
			SNDFrame** frames;

		public:
			SNDHeader(Functions::DataReader* reader);
			virtual ~SNDHeader();
			void SaveFileData(std::string location);
		};
	}
}

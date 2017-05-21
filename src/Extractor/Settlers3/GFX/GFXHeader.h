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
#include "../../../Functions/To.h"
#include "../../../Functions/File/DataReader.h"

namespace Extractor{
	namespace Settlers3{
		class GFXHeader {
		private:
			unsigned int fileID;     		//- @offset:00(4) File ID - 0x00041304
			unsigned int version;   		//- @offset:04(4) Version - 0x0c -- 12
			unsigned int spacer1; 			//- @offset:08(4) - 0
			unsigned int headerSize; 		//- @offset:12(4) - 0x54 -- 84
			unsigned int unknown16; 		//- @offset:16(4) - 0x20 -- 32
			unsigned int unknown20; 		//- @offset:20(4) - 0x40 -- 64
			unsigned int spacer2; 			//- @offset:24(4) - 0
			unsigned int colourBits; 		//- @offset:28(4) - 0x10 -- 16
			unsigned int colourCode1;		//- @offset:32(4) Colour depth - 0xf800/0x7c00 - 63488/31744
			unsigned int colourCode2;		//- @offset:36(4) - 0x07e0/0x03e0 -- 224
			unsigned int colourCode3;		//- @offset:40(4) - 0x1f -- 31
			unsigned int spacer3;			//- @offset:44(4) - 0
			unsigned int fileSize;			//- @offset:48(4) File Size
			unsigned int offsetText;		//- @offset:52(4)
			unsigned int offsetLandscape;	//- @offset:56(4)
			unsigned int offsetGui;			//- @offset:60(4)
			unsigned int offsetObject;		//- @offset:64(4)
			unsigned int offsetTorso; 		//- @offset:68(4)
			unsigned int offsetShadow; 		//- @offset:72(4)
			unsigned int offsetAnimation; 	//- @offset:76(4)
			unsigned int offsetPalette; 	//- @offset:80(4)

		public:
			GFXHeader(Functions::DataReader* reader);
			~GFXHeader(){};

			unsigned int ColourCode(){return this->colourCode1;}
			unsigned int OffsetData(){return this->offsetText;}
			unsigned int OffsetLandscape(){return this->offsetLandscape;}
			unsigned int OffsetGui(){return this->offsetGui;}
			unsigned int OffsetObject(){return this->offsetObject;}
			unsigned int OffsetTorso(){return this->offsetTorso;}
			unsigned int OffsetShadow(){return this->offsetShadow;}
			unsigned int OffsetAnimation(){return this->offsetAnimation;}
			unsigned int OffsetPalette(){return this->offsetPalette;}
		};
	}
}

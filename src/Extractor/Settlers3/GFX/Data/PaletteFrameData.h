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
#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/To.h"
#include "PaletteImageData.h"

namespace Extractor{
	namespace Settlers3{
		class PaletteFrameData{
		private:

			unsigned int sequenceCode = 0;			//@offset:00(4) - 0x1402
			unsigned short sequenceHeaderSize = 0;	//@offset:04(2) - 8
			unsigned char sequenceUnknown06;		//@offset:06(1)
			unsigned char count = 0;				//@offset:07(1)

			PaletteImageData** frames=NULL;

		public:

			PaletteFrameData(Functions::DataReader* reader, unsigned int offset,RGBA* Palette = NULL);
			~PaletteFrameData();

			bool SaveFileData(std::string location);
		};
	}
}

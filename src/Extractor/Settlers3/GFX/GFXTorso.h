/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_SETTLERS3_GFX_GFXTORSO_H_
#define EXTRACTOR_SETTLERS3_GFX_GFXTORSO_H_

#include <string>
#include "../../../Functions/To.h"
#include "../../../Functions/FileFunctions.h"
#include "../../../Log.h"

#include "Data/PaletteFrameData.h"

namespace Extractor{
	namespace Settlers3{
		class GFXTorso {
		private:
			//Default Header
			unsigned int headerID;			//@offset:00(4)
			unsigned short headerSize;		//@offset:04(2)
			unsigned short count=0;			//@offset:06(2)
			unsigned int* headOffsets = 0;	//@offset:08(4*count)
			//Data
			PaletteFrameData** images=NULL;

		public:
			GFXTorso(Functions::DataReader* reader, unsigned int offset,RGBA* Palette = NULL);
			virtual ~GFXTorso();
			bool SaveFileData(std::string location);
			PaletteImageData* ReturnTorso(unsigned short image,unsigned char frame);
		};
	}
}
#endif

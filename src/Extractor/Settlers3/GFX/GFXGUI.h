/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
//============================================================================
// Name        : GFXGUI.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS3_GFX_GFXGUI_H_
#define EXTRACTOR_SETTLERS3_GFX_GFXGUI_H_

#include <string>
#include "../../../Functions/DataReader.h"
#include "../../../Functions/To.h"
#include "../../../Functions/FileFunctions.h"
#include "../../../Log.h"

#include "Data/RGBImageData.h"

namespace Extractor{
	namespace Settlers3{
		class GFXGUI {
		private:

			//Default Header
			unsigned int headerID;		//- @offset:00(4)
			unsigned short headerSize;	//- @offset:04(2)
			unsigned short count=0;		//- @offset:06(2)

			//Data
			RGBImageData** images=NULL;

		public:
			GFXGUI(Functions::DataReader* reader, unsigned int offset,unsigned int colourCode);
			virtual ~GFXGUI();
			bool SaveFileData(std::string location);
			RGBImageData* ReturnImage(unsigned short image){return this->images[image];};
		};
	}
}
#endif

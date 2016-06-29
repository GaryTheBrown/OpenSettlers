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
#include "../../../Functions/To.h"
#include "../../../Functions/File/Functions.h"
#include "Data/RGBImageData.h"

namespace Extractor{
	namespace Settlers3{
		class GFXLandscape{
		private:

			//Default Header
			unsigned int headerID;		//- @offset:00(4)
			unsigned short headerSize;	//- @offset:04(2)
			unsigned short count=0;		//- @offset:06(2)

			//Data
			RGBImageData** images=NULL;

		public:
			GFXLandscape(Functions::DataReader* reader, unsigned int offset,unsigned int colourCode);
			~GFXLandscape();
			bool SaveFileData(std::string location);
			RGBImageData* ReturnImage(unsigned short image){return this->images[image];};
		};
	}
}

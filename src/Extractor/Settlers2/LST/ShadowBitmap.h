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
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/Image/RGBImage.h"
#include "../../../Functions/Image/RGBA.h"

namespace Extractor{
	namespace Settlers2{
		class ShadowBitmap : public Functions::RGBImage{
		private:
			unsigned int unknown = 0;// (always 0 = hex 00 00 00 00)
			unsigned short paletteID = 0; //(always 1 = hex 01 00)
			signed short xRel;
			signed short yRel;
			unsigned int partSize = 0;
		public:
			ShadowBitmap(Functions::DataReader* reader);

			virtual void SaveToFile(std::string filename);
		};
	}
}

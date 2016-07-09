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
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/Image/PaletteImage.h"

namespace Extractor{
	namespace Settlers2{
		class RLECompressedBitmap : public Functions::PaletteImage{
		private:
			unsigned short zeroPointX = 0;
			unsigned short zeroPointY = 0;
			unsigned int unknown = 0;// (always 0 = hex 00 00 00 00)
			unsigned short width = 0;
			unsigned short height = 0;
			unsigned short paletteID = 0; //(always 1 = hex 01 00)
			unsigned int partSize = 0;
		public:
			RLECompressedBitmap(Functions::DataReader* reader);

			void SaveToFile(std::string location){};
		};
	}
}

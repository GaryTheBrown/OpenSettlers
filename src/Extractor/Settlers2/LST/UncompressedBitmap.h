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
		class UncompressedBitmap : public Functions::PaletteImage{
		private:
			unsigned short paletteID;
			unsigned int lengthOfData;
			unsigned short zeroPointX;
			unsigned short zeroPointY;
			unsigned long long unknown;

		public:
			UncompressedBitmap(Functions::DataReader* reader);

			void SaveFileData(std::string location);
		};
	}
}

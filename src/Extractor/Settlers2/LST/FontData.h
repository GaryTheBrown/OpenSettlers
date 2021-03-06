/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS2_LST_FONTDATA_H
#define EXTRACTOR_SETTLERS2_LST_FONTDATA_H
#include <string>
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/Image/FileImage.h"
#include "../../../Functions/To.h"

namespace Extractor{
	namespace Settlers2{
		class FontData{
		private:
			const static unsigned char count = 224;

			unsigned char xSpacing;
			unsigned char ySpacing;

			unsigned char* imageData[count];

			RGBA* palette = NULL;
		public:
			explicit FontData(Functions::DataReader* reader);
			~FontData();

			void SetPalette(RGBA* palette){this->palette = palette;};
			void SaveToFile(std::string filename);
		};
	}
}

#endif
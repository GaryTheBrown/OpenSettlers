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
#include "../../../Functions/Image/Palette.h"
#include "../../../Functions/File/Save.h"

namespace Extractor{
	namespace Settlers2{
		class PaletteData{
		private:
			RGBA* palette = NULL;

		public:
			PaletteData(Functions::DataReader* reader);
			~PaletteData(){delete [] this->palette;};

			RGBA* GetPalette(){return this->palette;};
			void SaveFileData(std::string location);
		};
	}
}

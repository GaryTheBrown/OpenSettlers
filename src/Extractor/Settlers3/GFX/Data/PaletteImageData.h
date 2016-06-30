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
#include "../../../../Functions/Image/PaletteImageData.h"
#include "RGBImageData.h"
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/File/Save.h"
#include "../../../../Functions/To.h"
#include "../../../../Functions/File/Image.h"
#include "../../../../Functions/Image/RGBA.h"

namespace Extractor{
	namespace Settlers3{
		class PaletteImageData : public Functions::PaletteImageData{
		private:
			//header
			signed short xRel;
			signed short yRel;

		public:
			PaletteImageData(Functions::DataReader* reader, unsigned int offset,RGBA* Palette = NULL);
			virtual ~PaletteImageData(){};

			virtual void SaveToFile(std::string filename);
		};
	}
}

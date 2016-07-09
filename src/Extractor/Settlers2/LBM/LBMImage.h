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
#include "../../../Functions/File/Image.h"
#include "../../../Functions/Image/PaletteImage.h"
#include "../../../Log.h"
#include "../../../Functions/To.h"

namespace Extractor{
	namespace Settlers2{
		class LBMImage : public Functions::PaletteImage{
		public:
			LBMImage(Functions::DataReader* reader,unsigned short width,unsigned short height,RGBA* palette);
			virtual void SaveToFile(std::string filename);

			bool StepAnimation();
		};
	}
}

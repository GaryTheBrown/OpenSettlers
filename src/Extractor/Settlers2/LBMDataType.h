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
#include "../../LogSystem/LogSystem.h"
#include "../../Log.h"
#include "../../Functions/File/DataReader.h"
#include "../../Functions/To.h"
#include "../../Functions/File/Functions.h"
#include "../../Functions/File/Save.h"
#include "../../Functions/Image/RGBA.h"
#include "../../Functions/Image/PaletteData.h"
#include "LBM/LBMHeader.h"
#include "LBM/LBMBMHD.h"
#include "LBM/LBMAnimationData.h"
#include "LBM/LBMImage.h"

namespace Extractor {
	namespace Settlers2{
		class LBMDataType{
		private:
			LBMHeader* fileHeader = NULL;
			LBMBMHD* pictureHeader = NULL;
			Functions::PaletteData* palette = NULL;
			LBMAnimationData* animationData[16] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; //array of pointers to data
			LBMImage* imageData = NULL;

			unsigned short animationCount = 0;

		public:
			LBMDataType(std::string file);
			~LBMDataType();

			void SaveFileData(std::string location);
		};
	}
}

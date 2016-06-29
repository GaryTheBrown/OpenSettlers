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
#include "../../Functions/DataReader.h"
#include "../../Functions/To.h"
#include "../../Functions/File/Functions.h"
#include "../../Functions/File/Save.h"
#include "../../Functions/Image/RGBA.h"
#include "LBM/LBMHeader.h"
#include "LBM/LBMBMHD.h"
#include "LBM/LBMPalette.h"
#include "LBM/LBMAnimationData.h"
#include "LBM/LBMImage.h"

namespace Extractor {
	namespace Settlers2{
		class LBMDataType{
		private:
			LBMHeader* fileHeader = NULL;
			LBMBMHD* pictureHeader = NULL;
			LBMPalette* palette = NULL;
						//DPPS (Deluxe Paint III perspective)
			LBMAnimationData* animationData[16] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; //array of pointers to data
			LBMHeader* previewImage = NULL; //Not really need
			LBMImage* imageData = NULL;

		public:
			LBMDataType(std::string file);
			~LBMDataType();
		};
	}
}

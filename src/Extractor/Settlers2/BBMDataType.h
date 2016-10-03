/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
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

namespace Extractor{
	namespace Settlers2{
		class BBMDataType{
		private:
			LBMHeader* fileHeader = NULL;
			LBMBMHD* pictureHeader = NULL;
			Functions::PaletteData* palette = NULL;
			LBMAnimationData* animationData[16] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; //array of pointers to data

			unsigned short animationCount = 0;

		public:
			BBMDataType(std::string file);
			~BBMDataType();

			void SaveToFile(std::string location);
		};
	}
}

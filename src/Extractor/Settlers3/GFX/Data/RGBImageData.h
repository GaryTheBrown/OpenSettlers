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
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/File/Image.h"
#include "../../../../Functions/Image/RGBA.h"
#include "../../../../Functions/Image/RGBImageData.h"
#include "../../../../Functions/File/Save.h"
#include "../../../../Functions/To.h"

namespace Extractor{
	namespace Settlers3{
		class RGBImageData : public Functions::RGBImageData{
		public:
			enum enumIMGType{
				IMG_GFX_none,
				IMG_GFX_Landscape,
				IMG_GFX_Gui,
				IMG_GFX_Object,
				IMG_GFX_Shadow,
				IMG_GFX_Torso
			};

		private:
			//Header Info
			signed short xRel;
			signed short yRel;
			enumIMGType gfxType;

		public:
			RGBImageData(Functions::DataReader* reader, unsigned int offset, enumIMGType gfxType, unsigned int colourCode);
			RGBImageData(RGBA* imageRGBA, enumIMGType gfxType, unsigned short height, unsigned short width, signed short xRel,signed short yRel);
			RGBImageData(RGBA* imageRGBA, unsigned short height,unsigned short width,signed short xRel,signed short yRel);
			virtual ~RGBImageData(){};

			virtual void SaveToFile(std::string filename);
			virtual void SaveToRGBBMP(std::string filename);
		};
	}
}

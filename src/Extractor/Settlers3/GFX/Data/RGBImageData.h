/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_SETTLERS3_GFX_DATA_RGBIMAGEDATA_H_
#define EXTRACTOR_SETTLERS3_GFX_DATA_RGBIMAGEDATA_H_

#include <string>
#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/File/Image.h"
#include "../../../../Functions/RGBA.h"
#include "../../../../Functions/File/Save.h"
#include "../../../../Functions/To.h"

namespace Extractor{
	namespace Settlers3{
		class RGBImageData{
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
			unsigned short width;
			unsigned short height;
			signed short xRel;
			signed short yRel;

			RGBA* imageRGBA = NULL;
			enumIMGType gfxType;

		public:
			RGBImageData(Functions::DataReader* reader, unsigned int offset, enumIMGType gfxType, unsigned int colourCode);
			RGBImageData(RGBA* imageRGBA, enumIMGType gfxType, unsigned short height, unsigned short width, signed short xRel,signed short yRel);
			RGBImageData(RGBA* imageRGBA, unsigned short height,unsigned short width,signed short xRel,signed short yRel);
			virtual ~RGBImageData();

			void SaveToFile(std::string filename);
			void SaveToRGBBMP(std::string filename);

			//Image Manipulation
			RGBImageData* CutOutSection(unsigned short X,unsigned short Y,unsigned short height,unsigned short width);
			void ChangeColour(RGBA From, RGBA To);
			void ChangeColourRange(RGBA From, RGBA To, RGBA Range);
			void OverwriteSection(unsigned short X,unsigned short Y,unsigned short height,unsigned short width, RGBA colour = {0,0,0,0});
		};
	}
}

#endif

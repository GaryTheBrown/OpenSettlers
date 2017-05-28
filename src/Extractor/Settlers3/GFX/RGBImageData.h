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
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/Image/RGBA.h"
#include "../../../Functions/Image/RGBImage.h"
#include "../../../Functions/File/Save.h"
#include "../../../Functions/To.h"

namespace Extractor{
	namespace Settlers3{
		class RGBImageData : public Functions::RGBImage{
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
			enumIMGType gfxType;
		public:
			RGBImageData(Functions::DataReader* reader, unsigned int offset, enumIMGType gfxType, unsigned int colourCode);
			RGBImageData(RGBA* imageRGBA, enumIMGType gfxType, unsigned short width, unsigned short height, signed short xRel,signed short yRel);
			RGBImageData(RGBA* imageRGBA, unsigned short width,unsigned short height,signed short xRel,signed short yRel);
			virtual void SaveToFile(std::string filename);

			bool Keep(){return this->keep;};

			RGBImageData* ReturnImage(){this->keep = true; return this;}


		};
	}
}

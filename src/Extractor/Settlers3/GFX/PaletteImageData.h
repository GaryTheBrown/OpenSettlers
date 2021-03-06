/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS3_GFX_PALETTEIMAGEDATA_H
#define EXTRACTOR_SETTLERS3_GFX_PALETTEIMAGEDATA_H
#include <string>
#include "../../../Functions/Image/PaletteImage.h"
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/Image/RGBA.h"
//#include "RGBImageData.h"

namespace Extractor{
	namespace Settlers3{
		class PaletteImageData : public Functions::PaletteImage{
		private:
			bool keep = false;
		public:
			PaletteImageData(Functions::DataReader* reader, unsigned int offset,RGBA* Palette = NULL);

			const bool Keep(){return this->keep;};

			PaletteImageData* ReturnImage(){this->keep = true; return this;}
		};
	}
}

#endif
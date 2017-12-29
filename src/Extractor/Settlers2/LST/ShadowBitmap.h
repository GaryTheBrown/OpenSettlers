/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS2_LST_SHADOWBITMAP_H
#define EXTRACTOR_SETTLERS2_LST_SHADOWBITMAP_H
#include <string>
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/Image/RGBImage.h"
#include "../../../Functions/Image/RGBA.h"

namespace Extractor{
	namespace Settlers2{
		class ShadowBitmap : public Functions::RGBImage{
		private:

		public:
			explicit ShadowBitmap(Functions::DataReader* reader);

			virtual void SaveToFile(std::string filename);
		};
	}
}

#endif
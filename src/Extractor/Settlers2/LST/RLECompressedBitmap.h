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
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/Image/PaletteImage.h"

namespace Extractor{
	namespace Settlers2{
		class RLECompressedBitmap : public Functions::PaletteImage{
		public:
			RLECompressedBitmap(Functions::DataReader* reader);
		};
	}
}

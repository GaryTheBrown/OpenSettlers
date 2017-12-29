/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS2_LBM_LBMANIMATIONDATA_H
#define EXTRACTOR_SETTLERS2_LBM_LBMANIMATIONDATA_H
#include <string>
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/File/Save.h"
#include "../../../Functions/To.h"

namespace Extractor{
	namespace Settlers2{
		class LBMAnimationData{
		private:
			unsigned short padding;
			unsigned short rate;
			unsigned short flags;
			unsigned char low;
			unsigned char high;
			bool active = true;
			bool direction = true;

		public:
			explicit LBMAnimationData(Functions::DataReader* reader);

			std::string ToString();
		};
	}
}

#endif
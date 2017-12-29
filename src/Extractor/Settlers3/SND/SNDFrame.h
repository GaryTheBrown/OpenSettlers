/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS3_SND_SNDFRAME_H
#define EXTRACTOR_SETTLERS3_SND_SNDFRAME_H
#include <string>
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/To.h"
#include "SNDData.h"

namespace Extractor{
	namespace Settlers3{
		class SNDFrame{
		private:
			//Frame Header
			unsigned int count;

			//Data
			SNDData** data;

		public:
			SNDFrame(Functions::DataReader* reader, unsigned int offset);
			~SNDFrame();
			void SaveToFile(std::string filename);
		};
	}
}

#endif
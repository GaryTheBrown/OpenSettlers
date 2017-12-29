/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS3_SND_SNDDATA_H
#define EXTRACTOR_SETTLERS3_SND_SNDDATA_H

#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/Audio/WAVData.h"

namespace Extractor{
	namespace Settlers3{
		class SNDData : public Functions::WAVData{

		public:
			SNDData(Functions::DataReader* reader, unsigned int offset);
		};
	}
}

#endif
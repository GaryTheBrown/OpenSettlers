/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_SETTLERS3_GFX_DATA_ANIMATIONDATA_H_
#define EXTRACTOR_SETTLERS3_GFX_DATA_ANIMATIONDATA_H_

#include <string>
#include <iostream>
#include <fstream>

#include "../../../../Log.h"

#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/File/Save.h"
#include "../../../../Functions/To.h"

namespace Extractor{
	namespace Settlers3{
		class AnimationData {
		private:
			unsigned int count;
			struct AnimationDataFrame{
				signed short posX;
				signed short posY;
				unsigned short object_file;
				unsigned short object_id;
				unsigned short torso_id;
				unsigned short torso_file;
				unsigned short shadow_id;
				unsigned short shadow_file;
				unsigned short object_frame;
				unsigned short torso_frame;
				signed short sound_flag1;
				signed short sound_flag2;
			} *frames = NULL;

		public:
			AnimationData(Functions::DataReader* reader, int offset);
			virtual ~AnimationData(){};

			void SaveToFile(std::string filename);
		};
	}
}

#endif

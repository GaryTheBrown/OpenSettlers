/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS3_MAP_MAPTEXT_H
#define EXTRACTOR_SETTLERS3_MAP_MAPTEXT_H
#include <string>
#include "../../../Log.h"
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/To.h"
#include "MAPParts.h"
namespace Extractor{
	namespace Settlers3{
		class MAPText : public MAPParts{
		private:
			std::string text;
		public:
			MAPText(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey);
			virtual std::string ToString();
		};
	}
}

#endif
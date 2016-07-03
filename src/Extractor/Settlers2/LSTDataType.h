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
#include "../../Functions/File/DataReader.h"
#include "../../Functions/File/Functions.h"
#include "../../Log.h"

namespace Extractor {
	namespace Settlers2{
		class LSTDataType{
		public:
			struct imageHead{
				unsigned short zeroPointX = 0;
				unsigned short zeroPointY = 0;
				unsigned int unknown = 0;// (always 0 = hex 00 00 00 00)
				unsigned short width = 0;
				unsigned short height = 0;
				unsigned short paletteID = 0; //(always 1 = hex 01 00)
				unsigned int partSize = 0;
			};

		private:

			unsigned short headerID = 0;
			unsigned int count = 0;

		public:
			LSTDataType(std::string file);
			~LSTDataType();

		};
	}
}

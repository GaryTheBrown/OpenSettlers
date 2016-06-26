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
#include "../../../Functions/DataReader.h"
#include "../../../Functions/File/Functions.h"
#include "../../../Functions/File/Save.h"
#include "../../../Functions/To.h"
#include "../../../Log.h"

namespace Extractor{
	namespace Settlers3{
		class GFXText{
		private:
			std::string Languages[8] = {
					"1.German_ISO-8859-2",
					"2.English_ASCII",
					"3.Italian_ISO-8859-1",
					"4.French_ISO-8859-1",
					"5.Polish_ISO-8859-2",
					"6.Spanish_ISO-8859-1",
					"7.Korean_EUC-KR",
					"8.Japanese_SHIFT_JIS"
			};

			//Header
			unsigned int headerID;		//- @offset:00(4)
			unsigned int headerSize;	//- @offset:04(4)
			unsigned short countA;		//- @offset:08(2) -- SPECIAL
			unsigned short countB;		//- @offset:10(2) -- SPECIAL

			std::string **strings;
		public:
			GFXText(Functions::DataReader* reader, unsigned int offset);
			virtual ~GFXText();

			bool SaveFileData(std::string location);
		};
	}
}

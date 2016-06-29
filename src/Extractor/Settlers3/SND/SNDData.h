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
#include "../../../Functions/To.h"
#include "../../../Functions/File/Functions.h"

namespace Extractor{
	namespace Settlers3{
		class SNDData{
		private:
			//File Header
			unsigned int length;
			unsigned short fileVersion;		//1
			unsigned short channels;		//1
			unsigned int samplesPerSecond;	//0x5622 = 22,050
			unsigned int bytesPerSecond;	//0xac44 - 44100htz
			unsigned short blockAlignment;	//2
			unsigned short bitsPerSample;	//0x10 - 16

			unsigned char* data;

		public:
			SNDData(Functions::DataReader* reader, unsigned int offset);
			~SNDData();
			void SaveFileData(std::string filename);
		};
	}
}

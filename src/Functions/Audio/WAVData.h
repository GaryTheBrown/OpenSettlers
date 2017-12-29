/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef FUNCTIONS_AUDIO_WAVDATA_H
#define FUNCTIONS_AUDIO_WAVDATA_H
#include <string>
#include "../File/Functions.h"

namespace Functions{
	class WAVData{
	protected:
		//File Header
		unsigned short fileVersion = 0;
		unsigned short channels = 0;
		unsigned int samplesPerSecond = 0;
		unsigned int bytesPerSecond = 0;
		unsigned short blockAlignment = 0;
		unsigned short bitsPerSample = 0;

		unsigned int length = 0;
		unsigned char* data = NULL;

	public:
		WAVData(){};
		WAVData(unsigned short fileVersion,unsigned short channels,unsigned int samplesPerSecond,unsigned int bytesPerSecond,unsigned short blockAlignment,unsigned short bitsPerSample);
		virtual ~WAVData(){delete[] this->data;};
		void SaveToFile(std::string filename);
	};
}

#endif
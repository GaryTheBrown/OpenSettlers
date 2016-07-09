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
#include "../File/Functions.h"

namespace Functions{
	class WAVData{
	protected:
		//File Header
		unsigned int length;
		unsigned short fileVersion;
		unsigned short channels;
		unsigned int samplesPerSecond;
		unsigned int bytesPerSecond;
		unsigned short blockAlignment;
		unsigned short bitsPerSample;

		unsigned char* data;

	public:

		virtual ~WAVData(){delete[] this->data;};
		void SaveToFile(std::string filename);
	};
}

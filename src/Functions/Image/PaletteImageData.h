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
#include "../Image/RGBA.h"

namespace Functions{
	class PaletteImageData{
	protected:
		//header
		unsigned short width = 0;
		unsigned short height = 0;

		//Data
		unsigned char* image=NULL;
		bool* transparency=NULL;
		unsigned char palette[1024]; // BGRA Format

	public:
		PaletteImageData(){};
		virtual ~PaletteImageData();

		virtual void SaveToFile(std::string filename){};

		void SetPalette(RGBA* Palette);
		RGBA* ConvertToRGBA();
	};
}

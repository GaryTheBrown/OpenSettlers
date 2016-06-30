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
#include "../File/Image.h"


namespace Functions{
	class RGBImageData{
		protected:
		unsigned short width = 0;
		unsigned short height = 0;

		RGBA* imageRGBA = NULL;

	public:
		RGBImageData(){};
		RGBImageData(RGBA* imageRGBA, unsigned short height,unsigned short width);
		virtual ~RGBImageData();

		virtual void SaveToFile(std::string filename){};
		void SaveToRGBBMP(std::string filename);

		//Image Manipulation
		RGBA* CutOutSection(unsigned short X,unsigned short Y,unsigned short height,unsigned short width);
		void ChangeColour(RGBA From, RGBA To);
		void ChangeColourRange(RGBA From, RGBA To, RGBA Range);
		void OverwriteSection(unsigned short X,unsigned short Y,unsigned short height,unsigned short width, RGBA colour = {0,0,0,0});
	};
}
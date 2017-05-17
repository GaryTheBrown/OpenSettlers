/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <string>
#include <algorithm>
#include "RGBA.h"
#include "FileImage.h"


namespace Functions{
	class RGBImage{
		protected:
		unsigned short width = 0;
		unsigned short height = 0;
		signed short xRel = 0;
		signed short yRel = 0;

		RGBA* imageRGBA = NULL;

		bool keep = false;

	public:
		RGBImage(){};
		RGBImage(unsigned short width,unsigned short height);
		RGBImage(RGBA* imageRGBA, unsigned short width, unsigned short height, signed short xRel = 0, signed short yRel = 0);
		virtual ~RGBImage();

		void SaveToFile(std::string filename);

		//Image Manipulation
		RGBImage* CutOutSection(unsigned short X,unsigned short Y,unsigned short width,unsigned short height);
		void ChangeColour(RGBA From, RGBA To);
		void ChangeColourRange(RGBA From, RGBA To, RGBA Range);
		void OverwriteSection(unsigned short X,unsigned short Y,unsigned short width,unsigned short height, RGBA colour = {0,0,0,0});
		void FlipVertical();
		void SetKeep(){this->keep = true;};
		bool GetKeep(){return this->keep;};

		unsigned short Width(){return this->width;};
		unsigned short Height(){return this->height;};
		RGBA* ImageRGBA(){return this->imageRGBA;};

	};
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef FUNCTIONS_IMAGE_PALETTEIMAGE_H
#define FUNCTIONS_IMAGE_PALETTEIMAGE_H

#include <string>
#include "RGBA.h"
#include "../File/Save.h"
#include "../To.h"
#include "FileImage.h"
#include "../../Log.h"
#include "ConvertPALtoRGB.h"

namespace Functions{
	class PaletteImage{
	protected:
		//header
		signed short xRel = 0;
		signed short yRel = 0;
		unsigned short height = 0;
		unsigned short width = 0;


		//Data
		unsigned char* image=NULL;
		bool* transparency=NULL;
		RGBA* palette=NULL;

		unsigned char* tempData = NULL;
		unsigned int tmpsize = 0;
		void RAWSAVETEMP(std::string filename);

	public:
		PaletteImage(){};
		PaletteImage(unsigned short width, unsigned short height);
		PaletteImage(unsigned char* image, unsigned short width, unsigned short height);
		virtual ~PaletteImage();
		virtual void SaveToFile(std::string filename);

		RGBA* ConvertToRGBA();
		void SetPalette(RGBA* Palette);

	};
}

#endif
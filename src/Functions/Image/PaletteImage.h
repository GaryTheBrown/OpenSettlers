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
#include "../File/Save.h"
#include "../To.h"
#include "../File/Image.h"
#include "../../Log.h"
#include "ConvertPALtoRGB.h"

namespace Functions{
	class PaletteImage{
	protected:
		//header
		signed short xRel;
		signed short yRel;
		unsigned short width = 0;
		unsigned short height = 0;

		//Data
		unsigned char* image=NULL;
		bool* transparency=NULL;
		RGBA* palette=NULL;

		unsigned char* tempData = NULL;
		unsigned int tmpsize;
		void RAWSAVETEMP(std::string filename);

	public:
		virtual ~PaletteImage();
		virtual void SaveToFile(std::string filename);

		RGBA* ConvertToRGBA();
		void SetPalette(RGBA* Palette);

	};
}

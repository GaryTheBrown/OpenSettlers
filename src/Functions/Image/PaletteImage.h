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
#include "../../Log.h"

namespace Functions{
	class PaletteImage{
	protected:
		//header
		unsigned short width = 0;
		unsigned short height = 0;

		//Data
		unsigned char* image=NULL;

		RGBA* palette=NULL;

	public:
		virtual ~PaletteImage();

		virtual void SaveToFile(std::string filename){};
		virtual RGBA* ConvertToRGBA();

		void SetPalette(RGBA* Palette);

	};
}

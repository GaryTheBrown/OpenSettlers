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
#include "../File/DataReader.h"
#include "../File/Save.h"
#include "RGBA.h"
#include "Palette.h"

namespace Functions{
	class PaletteData{
	protected:
		RGBA* palette = NULL;

	public:
		PaletteData(Functions::DataReader* reader);
		~PaletteData(){delete [] palette;};

		RGBA* GetPalette(){return this->palette;};
		void SetTransparentColour(unsigned short transClr);
		void SaveFileData(std::string location);
	};
}

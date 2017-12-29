/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef FUNCTIONS_IMAGE_PALETTEDATA_H
#define FUNCTIONS_IMAGE_PALETTEDATA_H

#include "../File/DataReader.h"
#include "../File/Save.h"
#include "RGBA.h"
#include "Palette.h"

namespace Functions{
	class PaletteData{
	protected:
		RGBA* palette = NULL;
	public:
		explicit PaletteData(Functions::DataReader* reader);
		~PaletteData(){delete [] palette;};

		RGBA* GetPalette(){return this->palette;};
		void SetTransparentColour(unsigned short transClr);
		void SaveToFile(std::string location);
	};
}

#endif
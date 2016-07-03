/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "PaletteImage.h"
namespace Functions{
	PaletteImage::~PaletteImage(){
		if (this->image != NULL)
			delete [] this->image;
	}

	void PaletteImage::SetPalette(RGBA* palette){
		if ((this->palette == NULL)||(this->palette != palette))
			this->palette = palette;
	}

	RGBA* PaletteImage::ConvertToRGBA(){
		RGBA *imageRGBA = new RGBA[this->height*this->width];

		for (int i = 0; i < (this->height*this->width);i++){
			imageRGBA[i] = this->palette[this->image[i]];
		}
		return imageRGBA;
	}
}

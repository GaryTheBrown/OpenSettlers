/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "PaletteImageData.h"
namespace Functions{
	PaletteImageData::~PaletteImageData(){
		delete[] this->image;
	}

	void PaletteImageData::SetPalette(RGBA* palette){
		this->palette = palette;
	}

	RGBA* PaletteImageData::ConvertToRGBA(){
		RGBA *imageRGBA = new RGBA[this->height*this->width];

		for (int i = 0; i < (this->height*this->width);i++){
			if(this->transparency != NULL){
				if (this->transparency[i] == true){
					imageRGBA[i] = {0,0,0,0};
					continue;
				}
			}
			imageRGBA[i] = this->palette[this->image[i]];
		}
		return imageRGBA;
	}
}

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

	void PaletteImageData::SetPalette(RGBA* Palette){
		for (signed short i = 0; i < 256; i++){//BGR order
			this->palette[(i*4)] = Palette[i].B;
			this->palette[(i*4)+1] = Palette[i].G;
			this->palette[(i*4)+2] = Palette[i].R;
			this->palette[(i*4)+3] = Palette[i].A;
		}
	}

	RGBA* PaletteImageData::ConvertToRGBA(){
		RGBA *imageRGBA = new RGBA[this->height*this->width];

		for (int i = 0; i < (this->height*this->width);i++){
			if(this->transparency[i] == true){
				imageRGBA[i].A = 0;
				imageRGBA[i].R = 0;
				imageRGBA[i].G = 0;
				imageRGBA[i].B = 0;
			}
			else{
				imageRGBA[i].B = this->palette[(((this->image[i])*4)+0)];
				imageRGBA[i].G = this->palette[(((this->image[i])*4)+1)];
				imageRGBA[i].R = this->palette[(((this->image[i])*4)+2)];
				imageRGBA[i].A = this->palette[(((this->image[i])*4)+3)];
			}
		}
		return imageRGBA;
	}
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "ConvertPALtoRGB.h"

RGBA* Functions::ConvertPALToRGBA(unsigned char* fromImage, bool* fromTransparency,	RGBA* fromPalette, unsigned int size){

	RGBA *imageRGBA = new RGBA[size];

	if(fromTransparency != NULL){
		for (int i = 0; i < (size);i++){
			if(fromTransparency[i] == true)
				imageRGBA[i] = {0,0,0,0};
			else
				imageRGBA[i] = fromPalette[fromImage[i]];
		}
	}else{
		for (int i = 0; i < (size);i++)
			imageRGBA[i] = fromPalette[fromImage[i]];
	}
	return imageRGBA;
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "LBMPalette.h"

namespace Extractor {
	namespace Settlers2{
		LBMPalette::LBMPalette(Functions::DataReader* reader) {

			this->palette = new RGBA[256];
			for(unsigned short i = 0; i < 256; i++){
				this->palette[i].R = reader->ReadChar();
				this->palette[i].G = reader->ReadChar();
				this->palette[i].B = reader->ReadChar();
				this->palette[i].A = 255;
			}
		}

		LBMPalette::~LBMPalette() {
			delete [] palette;
		}

		void LBMPalette::SetTransparentColour(unsigned short transClr){
			this->palette[(transClr & 0xFF)] = {0,0,0,0};
		}
	}
}

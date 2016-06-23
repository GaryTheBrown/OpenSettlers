/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_SETTLERS3_GFX_DATA_PALETTEIMAGEDATA_H_
#define EXTRACTOR_SETTLERS3_GFX_DATA_PALETTEIMAGEDATA_H_

#include <string>
#include "RGBImageData.h"
#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/FileSave.h"
#include "../../../../Functions/To.h"
#include "../../../../Functions/FileImage.h"
#include "../../../../Functions/RGBA.h"

namespace Extractor{
	namespace Settlers3{
		class PaletteImageData {
		private:
			//header
			unsigned short width;
			unsigned short height;
			signed short xRel;
			signed short yRel;

			//Data
			unsigned char* image=NULL;
			bool* transparency=NULL;
			unsigned char palette[1024]; // BGRA Format
			bool paletteCheck = false;
			bool keepTorso = false;

		public:
			PaletteImageData(Functions::DataReader* reader, unsigned int offset,RGBA* Palette = NULL);
			virtual ~PaletteImageData();

			void SetPalette(RGBA* Palette);
			void SetPalleteCheck(){this->paletteCheck = true;};
			void SaveToFile(std::string filename);
			RGBImageData* ConvertToRGBA();
		};
	}
}
#endif

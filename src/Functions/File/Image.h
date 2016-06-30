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
#include <iostream>
#include <fstream>
#include "../Image/RGBA.h"
#include "DataReader.h"
#include "../../Log.h"
#include "Save.h"

namespace Functions{
	class FileImage{
	public:
		enum SaveType{
			Save_Type_BMPv2,
			Save_Type_BMPv4//,
			//Save_Type_
		};

		private:
			SaveType saveRGBType, savePalType;

		public:
			FileImage(SaveType saveRGBType = Save_Type_BMPv4,SaveType savePalType = Save_Type_BMPv2);

			void SaveToRGBImage(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height,signed short xRel, signed short yRel);
			void SaveToPaletteImage(std::string filename,unsigned char* image, unsigned char* palette, unsigned short width, unsigned short height);
			RGBA* LoadImageToRGBA(std::string filename, unsigned short* width, unsigned short* height,signed short* xRel, signed short* yRel);

		private:
			//BMPv2 NO TRANSPANRENCY OUTSIDE OF OPENSETTLERS AS ALPHA IGNORED
			void SaveToRGBBMPv2(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height,signed short xRel, signed short yRel);
			void SaveToPaletteBMPv2(std::string filename,unsigned char* image, unsigned char* palette, unsigned short width, unsigned short height);
			RGBA* LoadBMPv2ToRGBA(DataReader* reader, unsigned short* width, unsigned short* height);

			//BMPv4 TRANSPANRENCY OUTSIDE OF OPENSETTLERS AS ALPHA USED
			void SaveToRGBBMPv4(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height,signed short xRel, signed short yRel);
	};
}

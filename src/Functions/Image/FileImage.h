/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
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

#include <SDL2/SDL_image.h>

#include <png.h>

#include "RGBA.h"
#include "../File/DataReader.h"
#include "../../Log.h"
#include "../File/Save.h"

namespace Functions{
	class FileImage{
	public:
		enum SaveType{
			Save_Type_BMPv2,
			Save_Type_BMPv4,
			Save_Type_PNG
		};

		private:
			SaveType saveRGBType, savePalType;

		public:
			FileImage(SaveType saveRGBType = Save_Type_PNG,SaveType savePalType = Save_Type_BMPv2);

			void SaveToRGBImage(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height);
			void SaveToPaletteImage(std::string filename,unsigned char* image, RGBA* palette, unsigned short width, unsigned short height);
			RGBA* LoadImageToRGBA(std::string filename, unsigned short* width, unsigned short* height);

		private:
			//BMPv2 NO TRANSPANRENCY OUTSIDE OF OPENSETTLERS AS ALPHA IGNORED
			void SaveToRGBBMPv2(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height);
			void SaveToPaletteBMPv2(std::string filename,unsigned char* image, RGBA* palette, unsigned short width, unsigned short height);
			RGBA* LoadBMPv2ToRGBA(DataReader* reader, unsigned short* width, unsigned short* height);

			//BMPv4 TRANSPANRENCY OUTSIDE OF OPENSETTLERS AS ALPHA USED
			void SaveToRGBBMPv4(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height);
			RGBA* LoadBMPv4ToRGBA(DataReader* reader, unsigned short* width, unsigned short* height);

			//PNG USING LIBPNG
			void SaveToPNG(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height);
			RGBA* LoadPNGToRGBA(std::string filename, unsigned short* width, unsigned short* height);
	};
}

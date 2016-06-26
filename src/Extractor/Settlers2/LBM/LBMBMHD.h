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
#include "../../../Functions/DataReader.h"

namespace Extractor {
	namespace Settlers2{
		class LBMBMHD{
		private:

			unsigned short width;//UINT16BE	width	Image width, in pixels
			unsigned short height;//UINT16BE	height	Image height, in pixels
			unsigned short xOrigin;//Where on screen, in pixels, the image's top-left corner is. Value is usually 0,0 unless image is part of a larger image or not fullscreen.
			unsigned short yOrigin;
			unsigned char numPlanes;//Number of planes in bitmap, 1 for monochrome, 4 for 16 color, 8 for 256 color or 0 if there is only a colormap, and no image data. (i.e. this file is just a colormap.)
			unsigned char mask;//1 = masked, 2 = transparent color, 3 = lasso (for MacPaint). Mask data is not considered a bit plane.
			unsigned char compression;//If 0 then uncompressed. If 1 then image data is RLE compressed. Other values are theoretically possible, representing other compression methods.
			unsigned char pad1;//Ignore when reading, set to 0 when writing for future compatibility
			unsigned short transClr;//	Transparent colour, useful only when mask >= 2
			unsigned char xAspect;//	Pixel aspect, a ratio width:height; used for displaying the image on a variety of different screen resolutions for 320x200 5:6 or 10:11
			unsigned char yAspect;
			unsigned short pageWidth;//	The size of the screen the image is to be displayed on, in pixels, usually 320×200
			unsigned short pageHeight;

		public:
			LBMBMHD(Functions::DataReader* reader);
			virtual ~LBMBMHD();

			unsigned short Width(){return this->width;};
			unsigned short Height(){return this->height;};
			unsigned char NumPlanes(){return this->numPlanes;};
			unsigned char Mask(){return this->mask;};
			unsigned char Compression(){return this->compression;};
			unsigned short TransClr(){return this->transClr;};
		};
	}
}

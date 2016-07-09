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
#include <vector>
#include "../../Functions/File/DataReader.h"
#include "../../Functions/File/Functions.h"
#include "../../Functions/To.h"
#include "../../Log.h"
#include "LST/XMIDIData.h"
#include "LST/WAVData.h"
#include "LST/RLECompressedBitmap.h"
#include "LST/FontData.h"
#include "LST/PaletteData.h"

#include "LST/UncompressedBitmap.h"

namespace Extractor {
	namespace Settlers2{
		class LSTDataType{
		private:

			unsigned short headerID = 0;
			unsigned int count = 0;

			unsigned short wavCount = 0;
			unsigned short xmidiCount = 0;
			unsigned short rleCompressedBitmapCount = 0;
			unsigned short fontCount = 0;
			unsigned short playerColoredBitmapCount = 0;
			unsigned short paletteCount = 0;
			unsigned short shadowBitmapCount = 0;
			unsigned short uncompressedBitmapCount = 0;

			//std::vector<XMIDIData> xMidiFiles;
			WAVData** wavFiles = NULL;
			XMIDIData** xmidiFiles = NULL;
			RLECompressedBitmap** rleCompressedBitmapFiles = NULL;
			FontData** fontFiles = NULL;

			PaletteData** paletteFiles = NULL;

			UncompressedBitmap** uncompressedBitmapFiles = NULL;

		public:
			LSTDataType(std::string file);
			~LSTDataType();
			void SaveFileData(std::string location);

		};
	}
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "GFXHeader.h"
namespace Extractor{
	namespace Settlers3{
		GFXHeader::GFXHeader(Functions::DataReader* reader) {
			reader->SetOffset(0);

			this->fileID = reader->ReadInt();
			this->version = reader->ReadInt();
			this->spacer1 = reader->ReadInt();
			this->headerSize = reader->ReadInt();
			this->unknown16 = reader->ReadInt();
			this->unknown20 = reader->ReadInt();
			this->spacer2 = reader->ReadInt();
			this->colourBits = reader->ReadInt();
			this->colourCode1 = reader->ReadInt();
			this->colourCode2 = reader->ReadInt();
			this->colourCode3 = reader->ReadInt();
			this->spacer3 = reader->ReadInt();
			this->fileSize = reader->ReadInt();
			this->offsetText = reader->ReadInt();
			this->offsetLandscape = reader->ReadInt();
			this->offsetGui = reader->ReadInt();
			this->offsetObject = reader->ReadInt();
			this->offsetTorso = reader->ReadInt();
			this->offsetShadow = reader->ReadInt();
			this->offsetAnimation = reader->ReadInt();
			this->offsetPalette = reader->ReadInt();
		}
	}
}

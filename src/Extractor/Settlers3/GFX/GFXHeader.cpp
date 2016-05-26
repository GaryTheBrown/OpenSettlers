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
			LOGSYSTEM->Log("Reading:GFX:Header...",2);
			reader->SetOffset(0);
			this->fileID = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:FileID:" + Functions::ToString(this->fileID),3);
			this->version = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Version:" + Functions::ToString(this->version),3);
			this->spacer1 = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Spacer:" + Functions::ToString(this->spacer1),3);
			this->headerSize = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:HeaderSize:" + Functions::ToString(this->headerSize),3);
			this->unknown16 = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Unknown16:" + Functions::ToString(this->unknown16),3);
			this->unknown20 = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Unknown20:" + Functions::ToString(this->unknown20),3);
			this->spacer2 = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Spacer:" + Functions::ToString(this->spacer2),3);
			this->colourBits = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:ColourBits:" + Functions::ToString(this->colourBits),3);
			this->colourCode1 = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:ColourCode1:" + Functions::ToString(this->colourCode1),3);
			this->colourCode2 = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:ColourCode2:" + Functions::ToString(this->colourCode2),3);
			this->colourCode3 = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:ColourCode3:" + Functions::ToString(this->colourCode3),3);
			this->spacer3 = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Spacer:" + Functions::ToString(this->spacer3),3);
			this->fileSize = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:FileSize:" + Functions::ToString(this->fileSize),3);
			this->offsetText = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Text Offset:" + Functions::ToString(this->offsetText),3);
			this->offsetLandscape = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Landscape Offset:" + Functions::ToString(this->offsetLandscape),3);
			this->offsetGui = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:GUI Offset:" + Functions::ToString(this->offsetGui),3);
			this->offsetObject = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Offset Offset:" + Functions::ToString(this->offsetObject),3);
			this->offsetTorso = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Torso Offset:" + Functions::ToString(this->offsetTorso),3);
			this->offsetShadow = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Shadow Offset:" + Functions::ToString(this->offsetShadow),3);
			this->offsetAnimation = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Animation Offset:" + Functions::ToString(this->offsetAnimation),3);
			this->offsetPalette = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Header:Palette Offset:" + Functions::ToString(this->offsetPalette),3);
		}
	}
}

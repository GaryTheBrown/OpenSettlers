/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "GFXLandscape.h"
namespace Extractor{
	namespace Settlers3{
		GFXLandscape::GFXLandscape(Functions::DataReader* reader, unsigned int offset,unsigned int colourCode){
			reader->SetOffset(offset);
			this->headerID = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Landscape:Header ID:" + Functions::ToString(this->headerID),3);
			this->headerSize = reader->ReadShort();
			LOGSYSTEM->Log("Reading:GFX:Landscape:Header Size:" + Functions::ToString(this->headerSize),3);
			this->count = reader->ReadShort();
			LOGSYSTEM->Log("Reading:GFX:Landscape:Count" + Functions::ToString(this->count),3);

			if (this->count>0){
				unsigned int offsets[this->count];
				LOGSYSTEM->Log("Reading:GFX:Landscape:Offsets:",3,false);
				for (unsigned short i = 0;i < this->count;i++){
					offsets[i] = reader->ReadInt();
					LOGSYSTEM->LogCont(Functions::ToString(offsets[i]) + ",",4);
				}
				LOGSYSTEM->newLine(3);

				this->images = new RGBImageData* [this->count];
				LOGSYSTEM->Log("Reading:GFX:Landscape:Images:",3,false);
				for (unsigned short i = 0;i < this->count;i++){
					this->images[i] = new RGBImageData(reader,offsets[i],RGBImageData::IMG_GFX_Landscape,colourCode);
					LOGSYSTEM->LogCont(".",4);
				}
				LOGSYSTEM->newLine(3);
			}
		}

		GFXLandscape::~GFXLandscape(){
			if(this->images != NULL) {
				for(unsigned short i = 0; i < this->count; i++)
					delete this->images[i];
				delete[] this->images;
			}
		}

		bool GFXLandscape::SaveFileData(std::string location){
			if(this->count > 0){
				location += "/Landscape/";
				Functions::CreateDir(location);
				for(unsigned short i = 0; i < this->count; i++){
					if(this->images[i] != NULL) this->images[i]->SaveToFile(location + Functions::ToString(i));
				}
				return true;
			}
			return false;
		}
	}
}

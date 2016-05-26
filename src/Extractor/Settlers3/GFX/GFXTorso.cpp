/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "GFXTorso.h"
namespace Extractor{
	namespace Settlers3{
		GFXTorso::GFXTorso(Functions::DataReader* reader, unsigned int offset,RGBA* Palette){
			reader->SetOffset(offset);

			this->headerID = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Torso:Header ID:" + Functions::ToString(this->headerID),3);
			this->headerSize = reader->ReadShort();
			LOGSYSTEM->Log("Reading:GFX:Torso:Header Size:" + Functions::ToString(this->headerSize),3);
			this->count = reader->ReadShort();
			LOGSYSTEM->Log("Reading:GFX:Torso:Count" + Functions::ToString(this->count),3);

			if (this->count>0){
				unsigned int offsets[this->count];
				LOGSYSTEM->Log("Reading:GFX:Torso:Offsets:",3,false);
				for (unsigned short i = 0;i < this->count;i++){
					offsets[i] = reader->ReadInt();
					LOGSYSTEM->LogCont(Functions::ToString(offsets[i]) + ",",4);
				}
				LOGSYSTEM->newLine(3);

				this->images = new PaletteFrameData*[this->count];
				LOGSYSTEM->Log("Reading:Torso:GUI:Images:",3,false);
				for (unsigned short i = 0;i < this->count;i++){
					this->images[i] = new PaletteFrameData(reader,offsets[i],Palette);
					LOGSYSTEM->LogCont(".",4);
				}
				LOGSYSTEM->newLine(3);
			}
		}

		GFXTorso::~GFXTorso(){

			if(this->images != NULL){
				for (unsigned short i = 0; i < this->count; i++){
					if(this->images[i] != NULL) delete this->images[i];
				}
				delete[] this->images;
			}
		}

		bool GFXTorso::SaveFileData(std::string location){
			if(this->count > 0){
				location += "/Torso/";
				Functions::CreateDir(location);
				for(unsigned short i = 0; i < this->count; i++)
					if(this->images[i] != NULL) this->images[i]->SaveFileData(location + Functions::ToString(i));
				return true;
			}
			return false;
		}
		PaletteImageData* GFXTorso::ReturnTorso(unsigned short image,unsigned char frame){
			return this->images[image]->ReturnTorso(frame);
		};
	}
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "GFXObject.h"
namespace Extractor{
	namespace Settlers3{
		GFXObject::GFXObject(Functions::DataReader* reader, unsigned int offset,unsigned int colourCode){
			reader->SetOffset(offset);
			this->headerID = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Object:Header ID:" + Functions::ToString(this->headerID),3);
			this->headerSize = reader->ReadShort();
			LOGSYSTEM->Log("Reading:GFX:Object:Header Size:" + Functions::ToString(this->headerSize),3);
			this->count = reader->ReadShort();
			LOGSYSTEM->Log("Reading:GFX:Object:Count" + Functions::ToString(this->count),3);

			//- assign array for offsets
			if (this->count>0){
				unsigned int offsets[this->count];
				LOGSYSTEM->Log("Reading:GFX:Object:Offsets:",3,false);
				for (unsigned short i = 0;i < this->count;i++){
					offsets[i] = reader->ReadInt();
					LOGSYSTEM->LogCont(Functions::ToString(offsets[i]) + ",",4);
				}
				LOGSYSTEM->newLine(3);

				this->images = new RGBFrameData*[this->count];
				LOGSYSTEM->Log("Reading:GFX:Object:Images:",3,false);
				LOGSYSTEM->newLine(4);
				for (unsigned short i = 0;i < this->count;i++){
					this->images[i] = new RGBFrameData(reader,offsets[i],RGBImageData::IMG_GFX_Object,colourCode);
					LOGSYSTEM->LogCont(".",3,true);
				}
				LOGSYSTEM->newLine(3,true);
			}
		}

		GFXObject::~GFXObject(){
			if(this->images != NULL){
				LOGSYSTEM->Log("Deleting:GFX:Object:Images:",3,false);
				LOGSYSTEM->newLine(4);
				for (unsigned short i = 0; i < this->count; i++){
					if(this->images[i] != NULL) delete this->images[i];
					LOGSYSTEM->LogCont(".",3,true);
				}
				delete[] this->images;
				LOGSYSTEM->newLine(3,true);
			}
		}

		bool GFXObject::SaveFileData(std::string location){

			if(this->count > 0){
				location += "/Object/";
				Functions::CreateDir(location);
				LOGSYSTEM->Log("Saving:GFX:Landscape:Images:",3,false);
				LOGSYSTEM->newLine(4);
				for(unsigned short i = 0; i < this->count; i++){
					if(this->images[i] != NULL) this->images[i]->SaveFileData(location + Functions::ToString(i));
					LOGSYSTEM->LogCont(".",3,true);
				}
				LOGSYSTEM->newLine(3,true);
				return true;
			}
			return false;
		}
	}
}

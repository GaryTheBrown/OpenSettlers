/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "GFXAnimation.h"
namespace Extractor{
	namespace Settlers3{
		GFXAnimation::GFXAnimation(Functions::DataReader* reader, unsigned int offset){
			reader->SetOffset(offset);

			this->headerID = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Animation:Header ID:" + Functions::ToString(this->headerID),3);
			this->headerSize = reader->ReadShort();
			LOGSYSTEM->Log("Reading:GFX:Animation:Header Size:" + Functions::ToString(this->headerSize),3);
			this->count = reader->ReadShort();
			LOGSYSTEM->Log("Reading:GFX:Animation:Count" + Functions::ToString(this->count),3);

			//- assign array for offsets
			if (this->count>0){
				unsigned int offsets[this->count];
				LOGSYSTEM->Log("Reading:GFX:Animation:Offsets:",3,false);
				for (unsigned short i = 0;i < this->count;i++){
					offsets[i] = reader->ReadInt();
					LOGSYSTEM->LogCont(Functions::ToString(offsets[i]) + ",",4);
				}
				LOGSYSTEM->newLine(3);

				this->animations = new AnimationData*[this->count];
				LOGSYSTEM->Log("Reading:GFX:Animation:Images:",3,false);
				for (unsigned short i = 0;i < this->count;i++){
					this->animations[i] = new AnimationData(reader,offsets[i]);
					LOGSYSTEM->LogCont(".",4);
				}
				LOGSYSTEM->newLine(3);
			}
		}

		GFXAnimation::~GFXAnimation(){
			if(this->animations != NULL) delete[] this->animations;
		}

		bool GFXAnimation::SaveFileData(std::string location){
			if(this->count > 0){
				location += "/Animation/";
				Functions::CreateDir(location);
				for(unsigned short i = 0; i < this->count; i++){
					if(this->animations[i] != NULL) this->animations[i]->SaveToFile(location + Functions::ToString(i));
				}
				return true;
			}
			return false;
		}
	}
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "SNDFrame.h"
namespace Extractor{
	namespace Settlers3{
		SNDFrame::SNDFrame(Functions::DataReader* reader, unsigned int offset) {
			reader->SetOffset(offset);

			this->count = reader->ReadInt();

			unsigned int offsets[this->count];

			for (unsigned char i = 0; i < this->count; i++)
				offsets[i] = reader->ReadInt();

			this->data = new SNDData*[this->count];
			for (unsigned char i = 0; i < this->count; i++){
					this->data[i] = new SNDData(reader,offsets[i]);
			}
		}

		SNDFrame::~SNDFrame(){
			for (unsigned char i = 0; i < this->count; i++)
				delete this->data[i];
			delete[] this->data;
		}

		void SNDFrame::SaveFileData(std::string filename){
			for (unsigned short i = 0;i < this->count;i++){
				if (this->data[i] != NULL)
					this->data[i]->SaveFileData(filename + "_" + Functions::ToString(i) + ".wav");
			}
		}
	}
}

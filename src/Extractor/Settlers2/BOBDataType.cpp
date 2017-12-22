/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "BOBDataType.h"

Extractor::Settlers2::BOBDataType::BOBDataType(std::string file){

	if (Functions::FileExists(file) == true){
		Functions::DataReader* reader = new Functions::DataReader(file);

		//Make Sure File Is at 0
		reader->SetOffset(0);

		unsigned int header = reader->ReadInt();

		if (header != 0x01F501F6){
			LOGSYSTEM->Error("HEADER INVALID");
			delete reader;
			return;
		}

		unsigned short size = reader->ReadShort();
		unsigned int tempOffset2;
		unsigned int tempOffset1 = reader->GetOffset();

		reader->MoveOffset(size);

		for(unsigned int i = 0; i < 96; i++){

			unsigned short id = reader->ReadShort();

			if(id != 0x01F4){
				LOGSYSTEM->Error("ID (" + Functions::ToString(i) + ") INVALID");
				delete reader;
				return;
			}

			unsigned char height, ny;

			height = reader->ReadChar();
			unsigned int *starts = new unsigned int[height];

			for (unsigned char j = 0; j < height; j++)
				starts[j] = reader->ReadShort() + tempOffset1;

			ny = reader->ReadChar();

			//remember location
			tempOffset2 = reader->GetOffset();

			this->imageGroup1[i] = new PlayerColouredBitmap(reader,32,height,16,ny,NULL,starts,true);

			//restore location
			reader->SetOffset(tempOffset2);

			delete [] starts;
		}

		for(unsigned char i = 0; i < 6; i++){
			unsigned short id = reader->ReadShort();

			if(id != 0x01F5){
				delete reader;
				return;
			}

			this->part[i].size = reader->ReadShort();
			this->part[i].offset = reader->GetOffset();
			reader->MoveOffset(this->part[i].size);
		}

		this->goodCount = reader->ReadShort();

		Header* headerGroup = new Header[this->goodCount];

		for(unsigned short i = 0; i < this->goodCount; i++){
			unsigned short id = reader->ReadShort();

			if(id != 0x01F4){
				delete reader;
				return;
			}
			headerGroup[i].height = reader->ReadChar();
			headerGroup[i].starts = new unsigned int[headerGroup[i].height];

			for (unsigned int j = 0; j < headerGroup[i].height; j++)
				headerGroup[i].starts[j] = reader->ReadShort();

			headerGroup[i].ny = reader->ReadChar();
		}

		this->itemCount = reader->ReadShort();

		this->imageGroup2 = new LinkPart[this->itemCount];
		for(unsigned short i = 0; i < this->itemCount; ++i){
			this->imageGroup2[i].link = reader->ReadShort();
			//reader->ReadShort();

			//correct the offsets to be inside of the part section
			unsigned int* starts = new unsigned int[headerGroup[this->imageGroup2[i].link].height];
			for (unsigned char j = 0; j < headerGroup[this->imageGroup2[i].link].height; j++){
				starts[j] = headerGroup[this->imageGroup2[i].link].starts[j] + this->part[(i%6)].offset;
			}

			tempOffset2 = reader->GetOffset();

			this->imageGroup2[i].image = new PlayerColouredBitmap(reader,32,headerGroup[this->imageGroup2[i].link].height,16,headerGroup[this->imageGroup2[i].link].ny,NULL,starts,true);

			if(starts != NULL)
				delete [] starts;

			reader->SetOffset(tempOffset2);
			reader->MoveOffset(2);

		}

		delete [] headerGroup;
		delete reader;
	}
}

Extractor::Settlers2::BOBDataType::~BOBDataType() {
	for (unsigned int i = 0; i > 96; i++){
		delete this->imageGroup1[i];
	}

	for (unsigned short i = 0; i > this->goodCount; i++){
		delete this->imageGroup2[i].image;
	}
	delete [] this->imageGroup2;

}

void Extractor::Settlers2::BOBDataType::SaveToFile(std::string location){
	location += "/";
	for(unsigned int i = 0; i < 96; i++){
		this->imageGroup1[i]->SetPalette(this->Palette);
		this->imageGroup1[i]->SaveToFile(location + Functions::ToString((int)i));
	}
	for(unsigned short i = 0; i < this->itemCount; ++i){
		this->imageGroup2[i].image->SetPalette(this->Palette);
		this->imageGroup2[i].image->SaveToFile(location + Functions::ToString((int)i + 96));
	}
}


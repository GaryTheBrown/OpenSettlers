/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "BOBDataType.h"

Extractor::Settlers2::BOBDataType::BOBDataType(std::string file){

	unsigned int MaxHeight = 0;
	if (Functions::FileExists(file) == true){
		Functions::DataReader* reader = new Functions::DataReader(file);

		//Make Sure File Is at 0
		reader->SetOffset(0);

		unsigned int header = reader->ReadInt();

		if (header != 0x01F501F6){
			LOGSYSTEM->Error("HEADER INVALID");
			return;
		}

		unsigned short size = reader->ReadShort();

		reader->MoveOffset(size);

		unsigned int tempOffset;

		for(unsigned int i = 0; i < 96; i++){

			unsigned short id = reader->ReadShort();

			if(id != 0x01F4){
				LOGSYSTEM->Error("ID (" + Functions::ToString(i) + ") INVALID");
				return;
			}

			this->headerGroup1[i].height = reader->ReadChar();
			if (this->headerGroup1[i].height > MaxHeight) MaxHeight = this->headerGroup1[i].height;
			//this->headerGroup1[i].starts = new unsigned int[this->headerGroup1[i].height];
			for (unsigned char j = 0; j < this->headerGroup1[i].height; j++)
				this->headerGroup1[i].starts[j] = (reader->ReadShort() + 6);

			this->headerGroup1[i].ny = reader->ReadChar();

			//remember location
			tempOffset = reader->GetOffset();

			//this->imageGroup1[i] = new PlayerColouredBitmap(reader,32,height,16,ny,NULL,starts,true);
			//this->imageGroup1[i] = new PlayerColouredBitmap(reader,32,this->headerGroup1[i].height,16,this->headerGroup1[i].ny,NULL,this->headerGroup1[i].starts,true);

			//restore location
			reader->SetOffset(tempOffset);

			//delete [] this->headerGroup1[i].starts;
		}

		for(unsigned char i = 0; i < 6; i++){
			unsigned short id = reader->ReadShort();

			if(id != 0x01F5)
				return;

			this->part[i].size = reader->ReadShort();
			this->part[i].offset = reader->GetOffset();
			reader->MoveOffset(this->part[i].size);
		}

		this->goodCount = reader->ReadShort();

		bool* used = new bool[this->goodCount];
		for (unsigned short i = 0; i < this->goodCount; i++){
			used[i] = false;
		}

		this->headerGroup2 = new Header[this->goodCount];

		for(unsigned short i = 0; i < this->goodCount; i++){
			unsigned short id = reader->ReadShort();

			if(id != 0x01F4)
				return;
			this->headerGroup2[i].height = reader->ReadChar();
			if (this->headerGroup2[i].height > MaxHeight) MaxHeight = this->headerGroup2[i].height;
			//this->headerGroup2[i].starts = new unsigned int[this->headerGroup2[i].height];

			for (unsigned int j = 0; j < this->headerGroup2[i].height; j++)
				this->headerGroup2[i].starts[j] = reader->ReadShort();

			this->headerGroup2[i].ny = reader->ReadChar();
		}

		this->itemCount = reader->ReadShort();

		unsigned short link;

		for(unsigned short i = 0; i < this->itemCount; ++i){
			LOGSYSTEM->Log("(" + Functions::ToString(i) + "/" + Functions::ToString(this->itemCount) + ")");

			link = reader->ReadShort();
			if(!used[link]){
				LOGSYSTEM->Log("a");

				//correct the offsets
				for (unsigned char j = 0; j < this->headerGroup2[i].height; j++)
					this->headerGroup2[link].starts[j] = this->headerGroup2[link].starts[j] + this->part[i % 6].offset;

				tempOffset = reader->GetOffset();
				LOGSYSTEM->Log("b");

				//this->image[(link+96)] = new PlayerColouredBitmap(reader,32,heights[link],16,ny[link],NULL,(unsigned int*)starts[link],true);

//TODO FIX SEG FAULT HERE
				reader->SetOffset(tempOffset);
				LOGSYSTEM->Log("c");
			}

			used[link] = true;

			reader->MoveOffset(2);

			LOGSYSTEM->Log("d");
		}

		LOGSYSTEM->Log("finished rip");
		LOGSYSTEM->Log(Functions::ToString(MaxHeight));

	}
}
Extractor::Settlers2::BOBDataType::~BOBDataType() {
/*	for (unsigned int i = 0; i < 96; i++){
		delete [] this->headerGroup1[i].starts;
	}

	for (unsigned short i = 0; i < this->goodCount; i++){
		delete [] this->headerGroup2[i].starts;
	}
	*/
	delete [] this->headerGroup2;

	for (unsigned int i = 0; i > 96; i++){
		delete [] this->imageGroup1[i];
	}
	//delete [] this->imageGroup1;

	for (unsigned short i = 0; i > this->goodCount; i++){
		delete [] this->imageGroup2[i];
	}
	delete [] this->imageGroup2;

}

void Extractor::Settlers2::BOBDataType::SaveToFile(std::string location){
	location += "/";
//	for(unsigned int i = 0; i < this->images.size(); i++){
//		if(this->images[i] != NULL){
//			this->images[i]->SetPalette(this->Palette);
//			this->images[i]->SaveToFile(location + Functions::ToString(i));
//		}
//	}
}


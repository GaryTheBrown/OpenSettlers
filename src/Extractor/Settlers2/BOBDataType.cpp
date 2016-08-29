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

		this->images.resize(96);

		for(unsigned int i = 0; i < 96; i++){

			unsigned short id = reader->ReadShort();

			if(id != 0x01F4){
				LOGSYSTEM->Error("ID (" + Functions::ToString(i) + ") INVALID");
				return;
			}

			unsigned char height = reader->ReadChar();
			unsigned int* starts = new unsigned int[height];
			for (unsigned short j = 0; j < height; j++)
				starts[j] = 6 + reader->ReadShort();

			unsigned char ny = reader->ReadChar();

			//remember location
			unsigned int tempOffset = reader->GetOffset();

			PlayerColouredBitmap* image = new PlayerColouredBitmap(reader,32,height,16,ny,NULL,starts,true);
			delete this->images[i];
			this->images[i] = image;

			//restore location
			reader->SetOffset(tempOffset);

			delete [] starts;
		}

		unsigned short partSize[6];
		unsigned int partOffsets[6];

		for(unsigned int i = 0; i < 6; i++){
			unsigned short id = reader->ReadShort();

			if(id != 0x01F5)
				return;

			partSize[i] = reader->ReadShort();
			partOffsets[i] = reader->GetOffset();
			reader->MoveOffset(partSize[i]);
		}

		this->goodCount = reader->ReadShort();

		bool* used = new bool[this->goodCount];
		unsigned char* heights = new unsigned char[this->goodCount];
		//unsigned int** starts = new unsigned int*[this->goodCount];
		std::vector<unsigned int*> starts(this->goodCount);
		unsigned char* ny = new unsigned char[this->goodCount];

		for(unsigned short i = 0; i < this->goodCount; i++){
			unsigned short id = reader->ReadShort();

			if(id != 0x01F4)
				return;
			heights[i] = reader->ReadChar();

			starts[i] = new unsigned int[heights[i]];

			for (unsigned int j = 0; j < heights[i]; j++)
				starts[i][j] = reader->ReadShort();

			ny[i] = reader->ReadChar();
		}

		this->itemCount = reader->ReadShort();

		this->images.resize(this->images.size() + this->itemCount);

		for(unsigned int i = 0; i < this->itemCount; ++i){
			unsigned short link = reader->ReadShort();

			if(!used[link]){
				LOGSYSTEM->Log("a");

				//correct the offsets
				for (unsigned int j = 0; j < heights[i]; j++)
					starts[link][j] += partOffsets[i % 6];

				unsigned int tempOffsets = reader->GetOffset();
				LOGSYSTEM->Log("b");
				PlayerColouredBitmap* image = new PlayerColouredBitmap(reader,32,heights[link],16,ny[link],NULL,(unsigned int*)starts[link],true);


				LOGSYSTEM->Log("(" + Functions::ToString(i) + "/" + Functions::ToString(this->itemCount) + ") save to array:" + Functions::ToString((int)link+96) + " Vector Size:" + Functions::ToString(this->images.size()));
//TODO FIX SEG FAULT HERE
				this->images[(link+96)] = image;
				reader->SetOffset(tempOffsets);
				LOGSYSTEM->Log("c");
				if (starts[link] != NULL)
					delete [] starts[link];
			}

			used[link] = true;

			reader->MoveOffset(2);
		}

		starts.clear();
		delete [] ny;
	}
}
Extractor::Settlers2::BOBDataType::~BOBDataType() {

	this->images.clear();

}

void Extractor::Settlers2::BOBDataType::SaveToFile(std::string location){
	location += "/";
	for(unsigned int i = 0; i < this->images.size(); i++){
		if(this->images[i] != NULL){
			this->images[i]->SetPalette(this->Palette);
			this->images[i]->SaveToFile(location + Functions::ToString(i));
		}
	}
}


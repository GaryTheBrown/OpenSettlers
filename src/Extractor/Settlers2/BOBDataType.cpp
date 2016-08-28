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

		unsigned char* rawBase = new unsigned char[size];
		for (unsigned short i = 0; i < size; i++)
			rawBase[i] = reader->ReadChar();

		for(unsigned int i = 0; i < 96; i++){

			unsigned short id = reader->ReadShort();

			if(id != 0x01F4){
				LOGSYSTEM->Error("ID (" + Functions::ToString(i) + ") INVALID");
				return;
			}

			unsigned char height = reader->ReadChar();
			unsigned int* starts = new unsigned int[height];
			for (unsigned short j = 0; j < height; j++)
				starts[j] = reader->ReadShort();

			unsigned char ny = reader->ReadChar();

			this->imageGroup1[i] = new PlayerColouredBitmap(32,height,16,ny,rawBase,starts);

			if(this->imageGroup1[i] == NULL){
				LOGSYSTEM->Error("IMAGE FAILED TO READ");
				return;
			}
			delete [] starts;
		}
/*
		std::pair<unsigned short, unsigned char*> raw[6];

		for(unsigned int i = 0; i < 6; i++){
			unsigned short id = reader->ReadShort();

			if(id != 0x01F5)
				return;

			raw[i].first = reader->ReadShort();
			raw[i].second = new unsigned char[raw[i].first];
			for(unsigned int j = 0; j < raw[i].first; j++)
				raw[i].second[j] = reader->ReadChar();
		}

		this->goodCount = reader->ReadShort();
		bool* used = new bool[this->goodCount];

		unsigned char* heights = new unsigned char[this->goodCount];
		unsigned int** starts = new unsigned int*[this->goodCount];
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
		unsigned short* links = new unsigned short[this->itemCount];
		this->imageGroup2 = new PlayerColouredBitmap*[this->itemCount];

		for(unsigned int i = 0; i < this->itemCount; ++i){
			links[i] = reader->ReadShort();;
			if(!used[links[i]]){
				this->imageGroup2[i] = new PlayerColouredBitmap(32,heights[links[i]],16,ny[links[i]],raw[i % 6].second,starts[links[i]],true);
				delete [] starts[links[i]];
			}

			used[links[i]] = true;

			reader->MoveOffset(2);
		}
		for(unsigned int i = 0; i < 6; i++){
			delete [] raw[i].second;
		}

		delete [] links;
		delete [] starts;
		delete [] ny;
*/		delete [] rawBase;
	}
}
Extractor::Settlers2::BOBDataType::~BOBDataType() {

	for(unsigned int i = 0; i < 96; i++)
		delete this->imageGroup1[i];

//	for(unsigned int i = 0; i < this->itemCount; i++)
//		delete this->imageGroup2[i];
//	delete [] this->imageGroup2;

}

void Extractor::Settlers2::BOBDataType::SaveToFile(std::string location){
	location += "/";

	for(unsigned int i = 0; i < 96; i++)
			this->imageGroup1[i]->SaveToFile(location + Functions::ToString(i));

//	for(unsigned int i = 0; i < this->itemCount; i++)
//		if(this->imageGroup2[i] != NULL)
//			this->imageGroup2[i]->SaveToFile(location + Functions::ToString(96+i));

}


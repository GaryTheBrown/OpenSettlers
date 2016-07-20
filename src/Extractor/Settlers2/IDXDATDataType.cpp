/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "IDXDATDataType.h"

Extractor::Settlers2::IDXDATDataType::IDXDATDataType(std::string file){

	std::string secondFile = file.substr(0, file.find_last_of(".")) + ".DAT";

	//change from offsets to list from idx data.
	std::vector<unsigned int> xmidiList;
	std::vector<unsigned int> wavList;
	std::vector<unsigned int> rleCompressedBitmapList;
	std::vector<unsigned int> playerColouredBitmapList;
	std::vector<unsigned int> shadowBitmapList;
	std::vector<unsigned int> uncompressedBitmapList;
	std::vector<unsigned int> fontList;
	std::vector<unsigned int> paletteList;

	if (Functions::FileExists(file) == true){
		Functions::DataReader* reader = new Functions::DataReader(file);
		reader->SetOffset(0);
		this->count = reader->ReadInt();

		this->idxData = new IDXData[this->count];

		for (unsigned int i = 0; i < this->count; i++){
			this->idxData[i].name = reader->FetchBuffer(16);
			this->idxData[i].offset = reader->ReadInt();
			reader->MoveOffset(6);
			this->idxData[i].typeID = reader->ReadShort();
		}

		for (unsigned int i = 0; i < this->count; i++){
			switch(this->idxData[i].typeID){
			case 1:{//WAVMIDI:
				Functions::DataReader* reader2 = new Functions::DataReader(secondFile);
				reader2->SetOffset(this->idxData[i].offset + 2);
				reader2->MoveOffset(4);
				unsigned int fileType = reader->ReadInt();
				delete reader2;
				if (fileType == 1297239878)
					xmidiList.push_back(i);
				else
					wavList.push_back(i);
				break;
			}
			case 2://RLECompressedBitmap
				rleCompressedBitmapList.push_back(i);
				break;
			case 3://Font:
				fontList.push_back(i);
				LOGSYSTEM->Message("Font:" + Functions::ToString(this->idxData[i].offset)+ ":" + Functions::ToString((this->idxData[i+1].offset-this->idxData[i].offset)));
				break;
			case 4://PlayerColoredBitmap
				playerColouredBitmapList.push_back(i);
				break;
			case 5://Palette:
				paletteList.push_back(i);
				break;
			case 7://ShadowBitmap
				shadowBitmapList.push_back(i);
				break;
			case 14://UncompressedBitmap:
				uncompressedBitmapList.push_back(i);
				break;
			default://UNKNOWN IDS
				LOGSYSTEM->Error("Unknown File ID:" + Functions::ToString((int)this->idxData[i].typeID));
				return;
			}
		}
		delete reader;
	}

	this->wavCount = wavList.size();
	this->xmidiCount = xmidiList.size();
	this->rleCompressedBitmapCount = rleCompressedBitmapList.size();
	this->playerColouredBitmapCount = playerColouredBitmapList.size();
	this->shadowBitmapCount = shadowBitmapList.size();
	this->fontCount = fontList.size();
	this->paletteCount = paletteList.size();
	this->uncompressedBitmapCount = uncompressedBitmapList.size();

	if (Functions::FileExists(secondFile) == true){
		Functions::DataReader* reader = new Functions::DataReader(secondFile);

		if(this->wavCount > 0){
			this->wavFiles = new WAVData*[this->wavCount];

			for (unsigned int i = 0; i < this->wavCount; i++){
				reader->SetOffset(this->idxData[wavList[i]].offset);
				if (this->idxData[i].typeID == reader->ReadShort())
					this->wavFiles[i] = new WAVData(reader);
			}
		}
		if(this->xmidiCount > 0){
			this->xmidiFiles = new XMIDIData*[this->xmidiCount];

			for (unsigned int i = 0; i < this->xmidiCount; i++){
				reader->SetOffset(this->idxData[xmidiList[i]].offset);
				if (this->idxData[i].typeID == reader->ReadShort())
					this->xmidiFiles[i] = new XMIDIData(reader);
			}
		}
		if(this->rleCompressedBitmapCount > 0){
			this->rleCompressedBitmapFiles = new RLECompressedBitmap*[this->rleCompressedBitmapCount];

			for (unsigned int i = 0; i < this->rleCompressedBitmapCount; i++){
				reader->SetOffset(this->idxData[rleCompressedBitmapList[i]].offset);
				if (this->idxData[rleCompressedBitmapList[i]].typeID == reader->ReadShort())
					this->rleCompressedBitmapFiles[i] = new RLECompressedBitmap(reader);
			}
		}
		if(this->fontCount > 0){
			this->fontFiles = new FontData*[this->fontCount];

			for (unsigned int i = 0; i < this->fontCount; i++){
				reader->SetOffset(this->idxData[fontList[i]].offset);
				if (this->idxData[fontList[i]].typeID == reader->ReadShort())
					this->fontFiles[i] = new FontData(reader);
			}
		}
		if(this->playerColouredBitmapCount > 0){
			this->playerColouredBitmapFiles = new PlayerColouredBitmap*[this->playerColouredBitmapCount];

			for (unsigned int i = 0; i < this->playerColouredBitmapCount; i++){
				reader->SetOffset(this->idxData[playerColouredBitmapList[i]].offset);
				if (this->idxData[playerColouredBitmapList[i]].typeID == reader->ReadShort())
					this->playerColouredBitmapFiles[i] = new PlayerColouredBitmap(reader);
			}
		}
		if(this->paletteCount > 0){
			this->paletteFiles = new Functions::PaletteData*[this->paletteCount];

			for (unsigned int i = 0; i < this->paletteCount; i++){
				reader->SetOffset(this->idxData[paletteList[i]].offset);
				if (this->idxData[paletteList[i]].typeID == reader->ReadShort())
					this->paletteFiles[i] = new Functions::PaletteData(reader);
			}
		}
		if(this->shadowBitmapCount > 0){
			this->shadowBitmapFiles = new ShadowBitmap*[this->shadowBitmapCount];

			for (unsigned int i = 0; i < this->shadowBitmapCount; i++){
				reader->SetOffset(this->idxData[shadowBitmapList[i]].offset);
				if (this->idxData[shadowBitmapList[i]].typeID == reader->ReadShort())
					this->shadowBitmapFiles[i] = new ShadowBitmap(reader);
			}
		}
		if(this->uncompressedBitmapCount > 0){
			this->uncompressedBitmapFiles = new UncompressedBitmap*[this->uncompressedBitmapCount];

			for (unsigned int i = 0; i < this->uncompressedBitmapCount; i++){
				reader->SetOffset(this->idxData[uncompressedBitmapList[i]].offset);
				if (this->idxData[uncompressedBitmapList[i]].typeID == reader->ReadShort())
					this->uncompressedBitmapFiles[i] = new UncompressedBitmap(reader);
			}
		}
		delete reader;
	}
}
Extractor::Settlers2::IDXDATDataType::~IDXDATDataType() {

	delete [] this->idxData;

	if (this->wavFiles != NULL){
		for(unsigned short i = 0; i < this->wavCount; i++){
			delete this->wavFiles[i];
		}
		delete [] this->wavFiles;
	}
	if (this->xmidiFiles != NULL){
		for(unsigned short i = 0; i < this->xmidiCount; i++){
			delete this->xmidiFiles[i];
		}
		delete [] this->xmidiFiles;
	}
	if (this->rleCompressedBitmapFiles != NULL){
		for(unsigned short i = 0; i < this->rleCompressedBitmapCount; i++){
			delete this->rleCompressedBitmapFiles[i];
		}
		delete [] this->rleCompressedBitmapFiles;
	}
	if (this->fontFiles != NULL){
		for(unsigned short i = 0; i < this->fontCount; i++){
			delete this->fontFiles[i];
		}
		delete [] this->fontFiles;
	}
	if (this->playerColouredBitmapFiles != NULL){
		for(unsigned short i = 0; i < this->playerColouredBitmapCount; i++){
			delete this->playerColouredBitmapFiles[i];
		}
		delete [] this->playerColouredBitmapFiles;
	}
	if (this->paletteFiles != NULL){
		for(unsigned short i = 0; i < this->paletteCount; i++){
			delete this->paletteFiles[i];
		}
		delete [] this->paletteFiles;
	}
	if (this->shadowBitmapFiles != NULL){
		for(unsigned short i = 0; i < this->shadowBitmapCount; i++){
			delete this->shadowBitmapFiles[i];
		}
		delete [] this->shadowBitmapFiles;
	}
	if (this->uncompressedBitmapFiles != NULL){
		for(unsigned short i = 0; i < this->uncompressedBitmapCount; i++){
			delete this->uncompressedBitmapFiles[i];
		}
		delete [] this->uncompressedBitmapFiles;
	}
}

void Extractor::Settlers2::IDXDATDataType::SaveToFile(std::string location){
	location += "/";
	if (this->xmidiCount > 0){
		for(unsigned int i=0; i < this->xmidiCount; i++){
			Functions::CreateDir(location + "xMidi/");
			this->xmidiFiles[i]->SaveToFile(location + "xMidi/" + Functions::ToString(i) + ".xmi");
		}
	}
	if (this->wavCount > 0){
		for(unsigned int i=0; i < this->wavCount; i++){
			Functions::CreateDir(location + "WAV/");
			this->wavFiles[i]->SaveToFile(location + "WAV/" + Functions::ToString(i) + ".wav");
		}
	}
	if (this->rleCompressedBitmapCount > 0){
		for(unsigned int i=0; i < this->rleCompressedBitmapCount; i++){
			Functions::CreateDir(location + "RLECompressedBitmap/");
			this->rleCompressedBitmapFiles[i]->SetPalette(this->Palette);
			this->rleCompressedBitmapFiles[i]->SaveToFile(location + "RLECompressedBitmap/" + Functions::ToString(i));
		}
	}
	if (this->fontCount > 0){
		for(unsigned int i=0; i < this->fontCount; i++){
			Functions::CreateDir(location + "Font/");
			//TODO Find the correct palette for the fonts
			this->fontFiles[i]->SetPalette(this->paletteFiles[0]->GetPalette());//this->Palette);
			this->fontFiles[i]->SaveToFile(location + "Font/" + Functions::ToString(i));
		}
	}
	if (this->playerColouredBitmapCount > 0){
		for(unsigned int i=0; i < this->playerColouredBitmapCount; i++){
			Functions::CreateDir(location + "PlayerColouredBitmap/");
			this->playerColouredBitmapFiles[i]->SetPalette(this->Palette);
			this->playerColouredBitmapFiles[i]->SaveToFile(location + "PlayerColouredBitmap/" + Functions::ToString(i));
		}
	}
	if (this->paletteCount > 0){
		for(unsigned int i=0; i < this->paletteCount; i++){
			Functions::CreateDir(location + "Palette/");
			this->paletteFiles[i]->SaveToFile(location + "Palette/" + Functions::ToString(i));
		}
	}
	if (this->shadowBitmapCount > 0){
		for(unsigned int i=0; i < this->shadowBitmapCount; i++){
			Functions::CreateDir(location + "ShadowBitmap/");
			this->shadowBitmapFiles[i]->SaveToFile(location + "ShadowBitmap/" + Functions::ToString(i));
		}
	}
	if (this->uncompressedBitmapCount > 0){
		for(unsigned int i=0; i < this->uncompressedBitmapCount; i++){
			Functions::CreateDir(location + "UncompressedBitmap/");
			this->uncompressedBitmapFiles[i]->SetPalette(this->Palette);
			this->uncompressedBitmapFiles[i]->SaveToFile(location + "UncompressedBitmap/" + Functions::ToString(i));
		}
	}
}

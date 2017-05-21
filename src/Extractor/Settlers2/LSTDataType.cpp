/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "LSTDataType.h"

Extractor::Settlers2::LSTDataType::LSTDataType(std::string file){
	if (Functions::FileExists(file) == true){
		Functions::DataReader* reader = new Functions::DataReader(file);
		reader->SetOffset(0);//Make Sure File Is at 0

		this->headerID = reader->ReadShort();
		if (this->headerID == 20000){
			this->count = reader->ReadInt();
			std::vector<unsigned int> xmidiOffsets;
			std::vector<unsigned int> wavOffsets;
			std::vector<unsigned int> rleCompressedBitmapOffsets;
			std::vector<unsigned int> playerColouredBitmapOffsets;
			std::vector<unsigned int> shadowBitmapOffsets;
			std::vector<unsigned int> uncompressedBitmapOffsets;
			std::vector<unsigned int> fontOffsets;
			std::vector<unsigned int> paletteOffsets;

			for(unsigned int i = 0; i < this->count; i++){
				unsigned short itemActive = reader->ReadShort();
				if (itemActive > 0){ // If Active
					unsigned short itemID = reader->ReadShort();
					unsigned int offset = reader->GetOffset();
					switch(itemID){
					case 1:{//WAVMIDI:
						unsigned int partSize = reader->ReadInt();
						unsigned int fileType = reader->ReadInt();
						reader->MoveOffset(-4);
						if (fileType == 1297239878)
							xmidiOffsets.push_back(offset);
						else
							wavOffsets.push_back(offset);
						reader->MoveOffset(partSize);
						break;
					}
					case 2://RLECompressedBitmap
					case 4://PlayerColoredBitmap
					case 7:{//ShadowBitmap
						reader->MoveOffset(14);
						unsigned int partSize = reader->ReadInt();
						switch(itemID){
						case 2:
							rleCompressedBitmapOffsets.push_back(offset);
							break;
						case 4:
							playerColouredBitmapOffsets.push_back(offset);
							break;
						case 7:
							shadowBitmapOffsets.push_back(offset);
							break;
						}
						reader->MoveOffset(partSize);
						break;
					}
					case 3:{//Font:
						unsigned char xSpacing = reader->ReadChar();
						unsigned char ySpacing = reader->ReadChar();
						fontOffsets.push_back(offset);
						reader->MoveOffset(224*xSpacing*ySpacing);
						break;
					}
					case 5:{//Palette:
						reader->MoveOffset(770);
						paletteOffsets.push_back(offset);
						break;
					}
					case 14:{//UncompressedBitmap:
						LOGSYSTEM->Message("UNCOMPRESSED BITMAP");
						uncompressedBitmapOffsets.push_back(offset);
						reader->ReadShort();//paletteID
						unsigned int partSize = reader->ReadInt();
						reader->MoveOffset(partSize+16);
					}
					break;
					default://UNKNOWN IDS
						LOGSYSTEM->Error("Unknown File ID:" + Functions::ToString((int)itemID));
						return;
					}
				}
			}

			this->wavCount = wavOffsets.size();
			this->xmidiCount = xmidiOffsets.size();
			this->rleCompressedBitmapCount = rleCompressedBitmapOffsets.size();
			this->playerColouredBitmapCount = playerColouredBitmapOffsets.size();
			this->shadowBitmapCount = shadowBitmapOffsets.size();
			this->fontCount = fontOffsets.size();
			this->paletteCount = paletteOffsets.size();
			this->uncompressedBitmapCount = uncompressedBitmapOffsets.size();

			if(this->wavCount > 0){
				this->wavFiles = new WAVData*[this->wavCount];

				for (unsigned int i = 0; i < this->wavCount; i++){
					reader->SetOffset(wavOffsets[i]);
					this->wavFiles[i] = new WAVData(reader);
				}
			}
			if(this->xmidiCount > 0){
				this->xmidiFiles = new XMIDIData*[this->xmidiCount];

				for (unsigned int i = 0; i < this->xmidiCount; i++){
					reader->SetOffset(xmidiOffsets[i]);
					this->xmidiFiles[i] = new XMIDIData(reader);
				}
			}
			if(this->rleCompressedBitmapCount > 0){
				this->rleCompressedBitmapFiles = new RLECompressedBitmap*[this->rleCompressedBitmapCount];

				for (unsigned int i = 0; i < this->rleCompressedBitmapCount; i++){
					reader->SetOffset(rleCompressedBitmapOffsets[i]);
					this->rleCompressedBitmapFiles[i] = new RLECompressedBitmap(reader);
				}
			}
			if(this->fontCount > 0){
				this->fontFiles = new FontData*[this->fontCount];

				for (unsigned int i = 0; i < this->fontCount; i++){
					reader->SetOffset(fontOffsets[i]);
					this->fontFiles[i] = new FontData(reader);
				}
			}
			if(this->playerColouredBitmapCount > 0){
				this->playerColouredBitmapFiles = new PlayerColouredBitmap*[this->playerColouredBitmapCount];

				for (unsigned int i = 0; i < this->playerColouredBitmapCount; i++){
					reader->SetOffset(playerColouredBitmapOffsets[i]);
					this->playerColouredBitmapFiles[i] = new PlayerColouredBitmap(reader);
				}
			}
			if(this->paletteCount > 0){
				this->paletteFiles = new Functions::PaletteData*[this->paletteCount];

				for (unsigned int i = 0; i < this->paletteCount; i++){
					reader->SetOffset(paletteOffsets[i]);
					this->paletteFiles[i] = new Functions::PaletteData(reader);
				}
			}
			if(this->shadowBitmapCount > 0){
				this->shadowBitmapFiles = new ShadowBitmap*[this->shadowBitmapCount];

				for (unsigned int i = 0; i < this->shadowBitmapCount; i++){
					reader->SetOffset(shadowBitmapOffsets[i]);
					this->shadowBitmapFiles[i] = new ShadowBitmap(reader);
				}
			}
			if(this->uncompressedBitmapCount > 0){
				this->uncompressedBitmapFiles = new UncompressedBitmap*[this->uncompressedBitmapCount];

				for (unsigned int i = 0; i < this->uncompressedBitmapCount; i++){
					reader->SetOffset(uncompressedBitmapOffsets[i]);
					this->uncompressedBitmapFiles[i] = new UncompressedBitmap(reader);
				}
			}
		}else{
			LOGSYSTEM->Error("Not A LST File");
		}
	}
}
Extractor::Settlers2::LSTDataType::~LSTDataType() {

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

void Extractor::Settlers2::LSTDataType::SaveToFile(std::string location){
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
			this->fontFiles[i]->SetPalette(this->Palette);
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


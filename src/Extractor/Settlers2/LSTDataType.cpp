/*******************************************************************************
* Settlers Extractor - A program To extract data file for the Settlers 1-4
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
	this->tempPalette = new RGBA[256]{{0,0,0,0},{255,255,0,255},{255,219,23,255},{255,191,51,255},{251,159,75,255},{219,127,43,255},{187,99,19,255},{159,75,0,255},{87,51,39,255},{103,67,55,255},{123,87,71,255},{143,111,91,255},{163,135,115,255},{183,159,139,255},{203,183,167,255},{223,211,199,255},{255,191,179,255},{231,159,143,255},{211,131,115,255},{191,103,91,255},{171,79,67,255},{151,59,47,255},{131,39,31,255},{111,27,15,255},{91,15,7,255},{55,7,0,255},{91,47,19,255},{115,71,35,255},{139,99,55,255},{167,131,83,255},{191,163,115,255},{219,199,151,255},{99,87,75,255},{115,103,87,255},{135,123,107,255},{159,147,131,255},{179,167,151,255},{199,191,175,255},{219,211,199,255},{243,235,223,255},{0,63,23,255},{7,87,23,255},{15,111,19,255},{39,135,27,255},{75,159,43,255},{115,183,63,255},{155,207,87,255},{203,235,115,255},{91,27,19,255},{111,47,31,255},{135,71,51,255},{159,99,71,255},{183,131,99,255},{207,163,127,255},{231,195,159,255},{255,231,199,255},{147,27,27,255},{195,35,35,255},{223,99,99,255},{255,179,179,255},{0,27,123,255},{19,59,167,255},{51,103,211,255},{95,159,255,255},{123,59,19,255},{135,71,23,255},{147,87,31,255},{159,103,39,255},{171,119,47,255},{183,139,55,255},{195,159,67,255},{207,175,75,255},{219,195,87,255},{231,215,99,255},{243,235,111,255},{255,255,127,255},{179,167,143,255},{163,151,131,255},{147,139,123,255},{131,127,111,255},{83,55,39,255},{103,71,55,255},{115,79,63,255},{127,91,71,255},{135,103,79,255},{147,111,91,255},{159,123,99,255},{167,135,111,255},{179,147,123,255},{191,159,135,255},{199,171,147,255},{211,183,159,255},{223,199,175,255},{231,211,187,255},{243,223,203,255},{255,239,219,255},{35,39,35,255},{55,63,55,255},{79,87,79,255},{107,111,107,255},{131,139,131,255},{159,163,159,255},{183,187,183,255},{211,215,211,255},{75,27,67,255},{99,39,95,255},{123,55,123,255},{143,71,151,255},{159,95,175,255},{175,115,203,255},{191,139,227,255},{211,167,255,255},{51,51,59,255},{63,63,71,255},{71,75,83,255},{83,87,95,255},{95,99,111,255},{107,111,123,255},{119,127,135,255},{135,139,147,255},{147,155,163,255},{159,167,175,255},{171,179,187,255},{183,195,203,255},{199,207,215,255},{211,223,227,255},{223,235,239,255},{239,251,255,255},{0,211,247,255},{0,123,219,255},{0,55,191,255},{0,0,167,255},{255,255,0,255},{203,203,0,255},{151,151,0,255},{103,103,0,255},{255,0,0,255},{215,0,0,255},{175,0,0,255},{135,0,0,255},{187,151,231,255},{155,119,191,255},{123,91,155,255},{95,67,119,255},{119,119,119,255},{79,79,79,255},{39,39,39,255},{0,0,0,255},{99,247,175,255},{67,195,115,255},{43,143,63,255},{23,95,27,255},{255,187,71,255},{223,147,39,255},{195,107,15,255},{167,75,0,255},{255,251,243,255},{183,175,163,255},{115,103,95,255},{47,39,35,255},{0,27,35,255},{7,47,35,255},{15,59,27,255},{35,71,27,255},{71,83,47,255},{95,91,67,255},{103,99,75,255},{115,111,87,255},{123,123,95,255},{135,135,107,255},{143,147,119,255},{155,155,127,255},{163,167,139,255},{175,175,151,255},{183,187,167,255},{195,199,179,255},{0,47,123,255},{0,55,131,255},{0,63,139,255},{0,71,147,255},{0,83,155,255},{0,91,163,255},{0,103,171,255},{0,115,179,255},{0,127,187,255},{0,143,195,255},{0,155,203,255},{0,171,211,255},{31,183,215,255},{63,199,219,255},{99,211,223,255},{139,223,231,255},{143,115,91,255},{147,119,95,255},{155,127,99,255},{163,131,103,255},{171,139,107,255},{179,143,115,255},{187,151,119,255},{195,159,127,255},{199,171,135,255},{207,179,147,255},{215,191,155,255},{223,203,167,255},{231,211,175,255},{239,223,187,255},{247,231,199,255},{255,243,211,255},{55,39,11,255},{67,47,15,255},{79,59,23,255},{91,67,31,255},{107,79,39,255},{119,91,51,255},{131,103,63,255},{143,115,75,255},{159,131,91,255},{171,143,107,255},{183,159,123,255},{199,171,143,255},{211,187,163,255},{223,203,183,255},{235,219,203,255},{251,239,227,255},{19,51,0,255},{23,59,0,255},{31,71,0,255},{39,79,0,255},{47,91,7,255},{55,103,7,255},{67,115,11,255},{75,123,15,255},{91,135,19,255},{103,147,23,255},{115,159,31,255},{127,167,35,255},{139,179,43,255},{151,191,51,255},{167,203,59,255},{183,219,75,255},{0,99,135,255},{0,99,135,255},{0,103,135,255},{0,107,135,255},{0,107,135,255},{0,111,135,255},{0,115,135,255},{0,107,135,255},{167,59,11,255},{191,103,7,255},{215,159,0,255},{191,103,7,255},{0,0,0,255},{255,255,255,255},{255,0,143,255},{255,255,255,255}};
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
	if (this->tempPalette != NULL){
		delete [] this->tempPalette;
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
			this->rleCompressedBitmapFiles[i]->SetPalette(this->tempPalette);
			this->rleCompressedBitmapFiles[i]->SaveToFile(location + "RLECompressedBitmap/" + Functions::ToString(i));
		}
	}
	if (this->fontCount > 0){
		for(unsigned int i=0; i < this->fontCount; i++){
			Functions::CreateDir(location + "Font/");
			this->fontFiles[i]->SetPalette(this->tempPalette);
			this->fontFiles[i]->SaveToFile(location + "Font/" + Functions::ToString(i));
		}
	}
	if (this->playerColouredBitmapCount > 0){
		for(unsigned int i=0; i < this->playerColouredBitmapCount; i++){
			Functions::CreateDir(location + "PlayerColouredBitmap/");
			this->playerColouredBitmapFiles[i]->SetPalette(this->tempPalette);
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
			this->uncompressedBitmapFiles[i]->SetPalette(this->tempPalette);
			this->uncompressedBitmapFiles[i]->SaveToFile(location + "UncompressedBitmap/" + Functions::ToString(i));
		}
	}
}


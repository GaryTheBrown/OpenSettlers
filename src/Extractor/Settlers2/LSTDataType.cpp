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
			std::vector<unsigned int> playerColoredBitmapOffsets;
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
							playerColoredBitmapOffsets.push_back(offset);
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
			this->playerColoredBitmapCount = playerColoredBitmapOffsets.size();
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
					reader->SetOffset(fontOffsets[i]);
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

			if(this->paletteCount > 0){
				this->paletteFiles = new PaletteData*[this->paletteCount];

				for (unsigned int i = 0; i < this->paletteCount; i++){
					reader->SetOffset(paletteOffsets[i]);
					this->paletteFiles[i] = new PaletteData(reader);
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

	if (this->paletteFiles != NULL){
		for(unsigned short i = 0; i < this->paletteCount; i++){
			delete this->paletteFiles[i];
		}
		delete [] this->paletteFiles;
	}

	if (this->uncompressedBitmapFiles != NULL){
		for(unsigned short i = 0; i < this->uncompressedBitmapCount; i++){
			delete this->uncompressedBitmapFiles[i];
		}
		delete [] this->uncompressedBitmapFiles;
	}
}

void Extractor::Settlers2::LSTDataType::SaveFileData(std::string location){
	location += "/";
	if (this->xmidiCount > 0){
		for(unsigned int i=0; i < this->xmidiCount; i++){
			Functions::CreateDir(location + "xMidi/");
			this->xmidiFiles[i]->SaveFileData(location + "xMidi/" + Functions::ToString(i) + ".xmi");
		}
	}
	if (this->wavCount > 0){
		for(unsigned int i=0; i < this->wavCount; i++){
			Functions::CreateDir(location + "wav/");
			this->wavFiles[i]->SaveFileData(location + "wav/" + Functions::ToString(i) + ".wav");
		}
	}
	if (this->rleCompressedBitmapCount > 0){
		for(unsigned int i=0; i < this->rleCompressedBitmapCount; i++){
			Functions::CreateDir(location + "rleCompressedBitmap/");
			if (this->paletteCount == 1)this->rleCompressedBitmapFiles[i]->SetPalette(this->paletteFiles[1]->GetPalette());
			this->rleCompressedBitmapFiles[i]->SaveFileData(location + "rleCompressedBitmap/" + Functions::ToString(i));
		}
	}
	if (this->fontCount > 0){
		for(unsigned int i=0; i < this->fontCount; i++){
			Functions::CreateDir(location + "font/");
			if (this->paletteCount == 1)this->fontFiles[i]->SetPalette(this->paletteFiles[1]->GetPalette());
			this->fontFiles[i]->SaveFileData(location + "font/" + Functions::ToString(i));
		}
	}
	if (this->paletteCount > 0){
		for(unsigned int i=0; i < this->paletteCount; i++){
			Functions::CreateDir(location + "palette/");
			this->paletteFiles[i]->SaveFileData(location + "palette/" + Functions::ToString(i));
		}
	}

	if (this->uncompressedBitmapCount > 0){
		for(unsigned int i=0; i < this->uncompressedBitmapCount; i++){
			Functions::CreateDir(location + "UncompressedBitmap/");
			if (this->paletteCount == 1)this->uncompressedBitmapFiles[i]->SetPalette(this->paletteFiles[1]->GetPalette());
			this->uncompressedBitmapFiles[i]->SaveToFile(location + "UncompressedBitmap/" + Functions::ToString(i));
		}
	}
}


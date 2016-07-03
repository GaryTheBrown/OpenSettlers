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

namespace Extractor {
	namespace Settlers2{
		LSTDataType::LSTDataType(std::string file){

			if (Functions::FileExists(file) == true){
				Functions::DataReader* reader = new Functions::DataReader(file);

				//Make Sure File Is at 0
				reader->SetOffset(0);

				this->headerID = reader->ReadShort();
				LOGSYSTEM->Error("Header ID:" + Functions::ToString(this->headerID));
				if (this->headerID == 20000){
					this->count = reader->ReadInt();
					LOGSYSTEM->Error("Count:" + Functions::ToString(this->count));
					for(unsigned int i = 0; i < this->count; i++){
						unsigned short itemActive = reader->ReadShort();
						if (itemActive > 0){ // If Active
							unsigned short itemID = reader->ReadShort();
							switch(itemID){
								case 1:{//WAVMIDI:
									LOGSYSTEM->Error("WAV MIDI");
									unsigned int partSize = reader->ReadInt();
									unsigned int fileType = reader->ReadInt();
									if (fileType == 1297239878){
										LOGSYSTEM->Error("MIDI");
									}else{
										LOGSYSTEM->Error("WAV");
										reader->SetOffset((reader->GetOffset()-4));
									}
									LOGSYSTEM->Error("Part Size:" + Functions::ToString((int)partSize));
									reader->SetOffset((reader->GetOffset()+partSize));
									break;
								}
								case 2://RLECompressedBitmap
								case 4://PlayerColoredBitmap
								case 7:{//ShadowBitmap
									imageHead header;
									header.zeroPointX = reader->ReadSignedShort();
									header.zeroPointY = reader->ReadSignedShort();
									header.unknown = reader->ReadInt();
									header.width = reader->ReadShort();
									header.height = reader->ReadShort();
									header.paletteID = reader->ReadShort();
									header.partSize = reader->ReadInt();
									switch(itemID){
										case 2://RLECompressedBitmap:
											LOGSYSTEM->Error("RLECompressedBitmap");
											break;
										case 4://PlayerColoredBitmap:
											LOGSYSTEM->Error("PlayerColoredBitmap");
											break;
										case 7://ShadowBitmap:
											LOGSYSTEM->Error("ShadowBitmap");
											break;
									}
									LOGSYSTEM->Error("Part Size:" + Functions::ToString((int)header.partSize));
									reader->SetOffset((reader->GetOffset()+header.partSize));
									break;
								}
								case 3:{//Font:
									unsigned char xSpacing = reader->ReadChar();
									unsigned char ySpacing = reader->ReadChar();
									reader->SetOffset(reader->GetOffset()+(224*xSpacing*ySpacing));
									LOGSYSTEM->Error("Part Size:" + Functions::ToString((int)(224*xSpacing*ySpacing)));
									LOGSYSTEM->Error("Font");
									break;
								}
								case 5:{//Palette:
									unsigned short paletteID = reader->ReadShort();
									if (paletteID != 1){
										LOGSYSTEM->Error("Palette ID Wrong");
									}
									reader->SetOffset(reader->GetOffset()+768);
									LOGSYSTEM->Error("Part Size:770");
									LOGSYSTEM->Error("Palette");
									break;
								}
								case 14:{//UncompressedBitmap:
									unsigned short paletteID = reader->ReadShort();
									if (paletteID != 1){
										LOGSYSTEM->Error("Palette ID Wrong");
									}
									unsigned int partSize = reader->ReadInt();
									reader->SetOffset(reader->GetOffset()+partSize+16);
									LOGSYSTEM->Error("Uncompressed Bitmap");
								}
								break;
								default://UNKNOWN IDS
									LOGSYSTEM->Error("Unknown File ID:" + Functions::ToString((int)itemID));
									return;
							}
						}else{
							//LOGSYSTEM->Error("Item Not Active");
						}
					}
				}else{
					LOGSYSTEM->Error("Not A LST File");
				}
			}
		}
		LSTDataType::~LSTDataType() {
		}
	}
}

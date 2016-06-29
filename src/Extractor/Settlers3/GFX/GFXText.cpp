/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "GFXText.h"
namespace Extractor{
	namespace Settlers3{
		GFXText::GFXText(Functions::DataReader* reader, unsigned int offset){
			reader->SetOffset(offset);
				this->headerID = reader->ReadInt();
				this->headerSize = reader->ReadInt();
				this->countA = reader->ReadShort();
				this->countB = reader->ReadShort();

				int offsets[this->countB][this->countA];
				for (unsigned short i = 0; i < this->countB; i++){
					for (unsigned short j = 0; j < this->countA; j++){
						offsets[i][j] = reader->ReadInt();
					}
				}

				unsigned int size;
				this->strings = new std::string*[this->countB];
				for (unsigned short i = 0; i < this->countB; i++){
					this->strings[i] = new std::string[this->countA];
					for (unsigned short j = 0; j < this->countA; j++){
						if(j+1 < this->countA)
							size = offsets[i][j+1] - offsets[i][j];
						else
							size = offsets[i+1][0] - offsets[i][j];

						this->strings[i][j] = reader->ReadString(size,offsets[i][j]);
					}
				}
		}

		GFXText::~GFXText(){
			if(this->strings != NULL){
				for (unsigned short i = 0; i < this->countB; i++){
					delete[]this->strings[i];
				}
				delete[]this->strings;
			}
		}

		bool GFXText::SaveFileData(std::string location){
			if(this->countA > 0){
				location += "/Text/";
				Functions::CreateDir(location);
				std::string filename;
				std::string output;
				for (unsigned short i = 0; i < this->countB; i++){
					Functions::CreateDir(location + Languages[i] + "/");
					//if iconv
					Functions::iConverter converter(this->LanguageCodes[i]);
					for (unsigned short j = 0; j < this->countA; j++){
						filename = location + Languages[i] + "/" + Functions::ToString(j) + ".txt";

						//if iconv
						output = converter.convert(this->strings[i][j]);
						//else
						//output = this->strings[i][j];

						Functions::SaveToTextFile(filename,output);
					}
				}
				return true;
			}
			return false;
		}
	}
}

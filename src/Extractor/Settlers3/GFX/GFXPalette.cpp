/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "GFXPalette.h"
namespace Extractor{
	namespace Settlers3{
		GFXPalette::GFXPalette(Functions::DataReader* reader, unsigned int offset,unsigned int colourCode){
			reader->SetOffset(offset);

			this->headerID = reader->ReadInt();
			this->headerSize = reader->ReadShort();
			this->count = reader->ReadShort();
			this->sizeofPalette = reader->ReadInt();

			if (this->count>0){
				unsigned int offsets[this->count];
				for (unsigned short i = 0;i < this->count;i++){
					offsets[i] = reader->ReadInt();
				}

				this->palettes = new RGBA**[20];
				for(unsigned short i = 0; i < this->count; i++){
					this->palettes[i] = new RGBA*[8];
					for(unsigned char J = 0; J < 8; J++){
						this->palettes[i][J] = new RGBA[256];
					}
				}

				for(unsigned int i = 0; i < 20; i++){
					reader->SetOffset(offsets[i]);
					for(unsigned int j = 0; j < 8; j++){
						for(unsigned int k = 0; k < 256; k++){
							this->palettes[i][j][k] = RGBA(reader->ReadShort(),((colourCode == 0xf800)?true:false));
						}
						//- first colour is set to transparency if needed for later
						//this->palettes[i][j][0].R = 0;
						//this->palettes[i][j][0].G = 0;
						//this->palettes[i][j][0].B = 0;
						//this->palettes[i][j][0].A = 0;
					}
				}
			}
		}

		GFXPalette::~GFXPalette(){
			if (this->count == 20){
				if(this->palettes != NULL){
					for (unsigned short i = 0; i < this->count; i++){
						for (unsigned char j = 0; j < 8; j++){
							delete [] this->palettes[i][j];
						}
						delete [] this->palettes[i];
					}
					delete [] this->palettes;
				}
			}
		}

		bool GFXPalette::SaveToText(std::string location){
			if(this->count > 0){
				std::string data;
				for(int i = 0; i < this->count;i++){
					for(int j = 0; j < 8;j++){
						data = Functions::PaletteToText(this->palettes[i][j]);
						std::string filename = location + Functions::ToString(i) + "." + Functions::ToString(j) + ".txt";
						Functions::SaveToTextFile(filename,data);
					}
				}
				return true;
			}
			else
				return false;
		}

		bool GFXPalette::SaveToHtml(std::string location){
			if(this->count > 0){
				std::string htmlVersion = "<html><table>";
				for(int i = 0; i < this->count;i++){
					htmlVersion += "<tr><td><b>Group #" + Functions::ToString(i) + "</b></td>.";
					for(int j = 0; j < 8;j++){
						htmlVersion += "<td>Palette #" + Functions::ToString(j)+ "<br>";
						htmlVersion += Functions::PaletteToHtml(this->palettes[i][j]);
						htmlVersion += "</td>";
					}
					htmlVersion += "</tr>";
				}
				htmlVersion += "</table></html>";
				Functions::SaveToTextFile(location + "Palettes.html",htmlVersion);
				return true;
			}
			else
				return false;
		}

		bool GFXPalette::SaveFileData(std::string location){
			if((this->count > 0)&&(this->palettes != NULL)){
				location += "/Palette/";
				Functions::CreateDir(location);
				if (!this->SaveToText(location)) return false;
				if (!this->SaveToHtml(location)) return false;
				return true;
			}
			return false;
		}
	}
}

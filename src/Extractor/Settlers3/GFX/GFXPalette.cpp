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
		GFXPalette::GFXPalette(Functions::DataReader* reader, unsigned int offset,unsigned int colourCode) {
			reader->SetOffset(offset);

			this->headerID = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Palette:Header ID:" + Functions::ToString(this->headerID),3);
			this->headerSize = reader->ReadShort();
			LOGSYSTEM->Log("Reading:GFX:Palette:Header Size:" + Functions::ToString(this->headerSize),3);
			this->count = reader->ReadShort();
			LOGSYSTEM->Log("Reading:GFX:Palette:Count" + Functions::ToString(this->count),3);
			this->sizeofPalette = reader->ReadInt();
			LOGSYSTEM->Log("Reading:GFX:Palette:SizeOf" + Functions::ToString(this->sizeofPalette),3);

			if (this->count>0){
				unsigned int offsets[this->count];
				LOGSYSTEM->Log("Reading:GFX:Palette:Offsets:",3,false);
				for (unsigned short i = 0;i < this->count;i++){
					offsets[i] = reader->ReadInt();
					LOGSYSTEM->LogCont(Functions::ToString(offsets[i]) + ",",4);
				}
				LOGSYSTEM->newLine(3);

				this->palettes = new RGBA**[20];
				for(unsigned short i = 0; i < this->count; i++){
					this->palettes[i] = new RGBA*[8];
					for(unsigned char J = 0; J < 8; J++){
						this->palettes[i][J] = new RGBA[256];
					}
				}
				LOGSYSTEM->Log("Reading:GFX:Palette:Images:",3,false);
				LOGSYSTEM->newLine(4);
				for(unsigned short i = 0; i < 20; i++){
					reader->SetOffset(offsets[i]);
					for(unsigned char j = 0; j < 8; j++){
						for(unsigned short k = 0; k < 256; k++){
							this->palettes[i][j][k] = RGBA(reader->ReadShort(),((colourCode == 0xf800)?true:false));
						}
						LOGSYSTEM->LogCont(".",3,true);
						//- first colour is set to transparency if needed for later
						//this->palettes[i][j][0].R = 0;
						//this->palettes[i][j][0].G = 0;
						//this->palettes[i][j][0].B = 0;
						//this->palettes[i][j][0].A = 0;
					}
					LOGSYSTEM->newLine(3,true);
				}
			}
		}

		GFXPalette::~GFXPalette() {
			if (this->count == 20){
				if(this->palettes != NULL){
					LOGSYSTEM->Log("Deleting:GFX:Palette:Images:",3,false);
					LOGSYSTEM->newLine(4);
					for (unsigned short i = 0; i < this->count; i++){
						for (unsigned char j = 0; j < 8; j++){
							delete [] this->palettes[i][j];
						}
						delete [] this->palettes[i];
						LOGSYSTEM->LogCont(".",3,true);
					}
					delete [] this->palettes;
					LOGSYSTEM->newLine(3,true);
				}
			}
		}
//TODO LOGSYSTEM BELLOW
		bool GFXPalette::SaveToText(std::string location){


			if(this->count > 0){
				std::string data;
				for(int i = 0; i < this->count;i++){
					for(int j = 0; j < 8;j++){
						data = "";
						for(int k = 0; k < 256;k++){
							data += "[";
							data += Functions::ToString((unsigned int)this->palettes[i][j][k].R);
							data += ",";
							data += Functions::ToString((unsigned int)this->palettes[i][j][k].G);
							data += ",";
							data += Functions::ToString((unsigned int)this->palettes[i][j][k].B);
							data += ",";
							data += Functions::ToString((unsigned int)this->palettes[i][j][k].A);
							data += "]";
						}
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
						htmlVersion += "<td>Palette #" + Functions::ToString(j)+ "<br><table>";
						for(int k = 0; k < 16;k++){
							htmlVersion += "<tr>";
							for(int l = 0; l < 16;l++){
								int colour = ((int)this->palettes[i][j][k*16+l].R << 16) | ((int)this->palettes[i][j][k*16+l].G << 8) | (int)this->palettes[i][j][k*16+l].B;
								std::string hex = Functions::ToHex(colour,3);
								std::string textcolour = "#000000";
								if(this->palettes[i][j][k*16+l].R < 128 && this->palettes[i][j][k*16+l].G < 128 && this->palettes[i][j][k*16+l].B < 128)
									textcolour="#FFFFFF";


								htmlVersion += "<td bgcolor=#" + hex + "><font color=" + textcolour + ">" + hex + "</font></td>";
							}
							htmlVersion += "</tr>";
						}
						htmlVersion += "</table></td>";
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

		RGBA*** GFXPalette::ReturnPalettes(){
			return this->palettes;
		}
	}
}

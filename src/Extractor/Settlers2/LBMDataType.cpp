/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "LBMDataType.h"

Extractor::Settlers2::LBMDataType::LBMDataType(std::string file){

	if (Functions::FileExists(file) == true){
		Functions::DataReader* reader = new Functions::DataReader(file);

		//Make Sure File Is at 0
		reader->SetOffset(0);

		//Set Big Endian Mode
		reader->SetBigEndian();

		//Read File Header
		this->fileHeader = new LBMHeader(reader);

		while(reader->EndOfFile() == false){
			unsigned int partType = reader->ReadInt();
			unsigned int partSize = reader->ReadInt();

			switch(partType){
			case 1112361028://BMHD (Image Header)
				if(partSize == 20){
					this->pictureHeader = new LBMBMHD(reader);
				}
				else
					LOGSYSTEM->Error("Wrong Size for Image Header");
				break;
			case 1129136464://CMAP (Palette)
				if(partSize == 768){
					this->palette = new Functions::PaletteData(reader);
					this->palette->SetTransparentColour(this->pictureHeader->TransClr());
				}else
					LOGSYSTEM->Error("Wrong Size for Palette");
				break;
			case 1129467463://CRNG (animation info)
				if(partSize == 8){
					if(animationCount < 16){
						this->animationData[animationCount] = new LBMAnimationData(reader);
						this->animationCount++;
					}
					else
						LOGSYSTEM->Error("Extra Animation Data");
				}
				else
					LOGSYSTEM->Error("Wrong Size for Animation Data " + Functions::ToString((int)animationCount));
				break;

			case 1112491097://BODY (IMAGE Data (chars))
					this->imageData = new LBMImage(reader,this->pictureHeader->Width(),this->pictureHeader->Height(),this->palette->GetPalette());
				break;
			default:
				//skip the section
				reader->SetOffset((reader->GetOffset()+partSize));
				break;
			}
			if(reader->GetOffset()%2 == 1){
				reader->ReadChar(); //partSize is an Odd Number skip a char
			}
		}
	}
}
Extractor::Settlers2::LBMDataType::~LBMDataType() {
	if(this->fileHeader != NULL){
		delete this->fileHeader;
	}
	if(this->pictureHeader != NULL){
		delete this->pictureHeader;
	}
	if(this->palette != NULL){
		delete this->palette;
	}
	if(this->animationData != NULL){
		for(unsigned short i = 0; i < 16; i++){
			if(this->animationData[i] != NULL){
				delete this->animationData[i];
			}
		}
	}

	if(this->imageData != NULL){
		delete this->imageData;
	}
}

void Extractor::Settlers2::LBMDataType::SaveToFile(std::string location){
	location += "/";
	if (this->animationCount > 0){
		std::string data = "pad\trate\tflags\tlow\thigh\tacti\tdir\n";
		for (int i = 0; i < this->animationCount; i++){
			data += this->animationData[i]->ToString();
		}
		Functions::SaveToTextFile(location + "Animation.txt",data);
	}
	this->imageData->SaveToFile(location + "Image");

	if (this->palette != NULL){
		this->palette->SaveToFile(location + "Palette");
	}
}

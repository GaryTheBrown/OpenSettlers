/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "LBMDataType.h"

namespace Extractor {
	namespace Settlers2{
		LBMDataType::LBMDataType(std::string file) {

			if (Functions::FileExists(file) == true){
				Functions::DataReader* reader = new Functions::DataReader(file);

				unsigned short animationCount = 0;
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
							this->palette = new LBMPalette(reader);
						}else
							LOGSYSTEM->Error("Wrong Size for Palette");
						break;
					case 1146114131://DPPS (Deluxe Paint III perspective)
						//if(partSize == 110){
						reader->SetOffset((reader->GetOffset()+partSize));
						//}

						break;
					case 1129467463://CRNG (animation info)
						if(partSize == 8){
							if(animationCount < 16){
								this->animationData[animationCount] = new LBMAnimationData(reader);
								animationCount++;
							}
							else
								LOGSYSTEM->Error("Extra Animation Data");
						}
						else
							LOGSYSTEM->Error("Wrong Size for Animation Data " + Functions::ToString((int)animationCount));
						break;
					case 1414090329://TINY (preview image)
						reader->SetOffset((reader->GetOffset()+partSize));
						reader->ReadChar(); //partSize is an Odd Number Why?
						break;
					case 1112491097://BODY (IMAGE Data (chars))
							this->imageData = new LBMImage(reader,this->pictureHeader->Width(),this->pictureHeader->Height(),this->palette->Palette());
							reader->SetOffset(reader->GetOffset()+this->pictureHeader->Height()*this->pictureHeader->Width());
						break;
					default:
						//skip the section
						reader->SetOffset((reader->GetOffset()+partSize));
						break;
					}
				}
			}
		}
		LBMDataType::~LBMDataType() {
			if(this->fileHeader != NULL) delete this->fileHeader;
			if(this->pictureHeader != NULL) delete this->pictureHeader;
			if(this->palette != NULL) delete this->palette;
			for(unsigned short i = 0; i < 16; i++)
				if(this->animationData[i] != NULL) delete this->animationData[i];

			if(this->previewImage != NULL) delete this->previewImage;
			if(this->imageData != NULL) delete this->imageData;
		}
	}
}

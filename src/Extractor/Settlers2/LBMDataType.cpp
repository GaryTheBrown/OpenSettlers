//============================================================================
// Name        : LBMDataType.cpp
// Author      : Gary_The_Brown
// Description :
//============================================================================

#include "LBMDataType.h"

namespace Extractor {
	namespace Settlers2{
		LBMDataType::LBMDataType(Functions::DataReader* reader) {

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
					if(partSize == 768)
						this->palette = new LBMPalette(reader);
					else
						LOGSYSTEM->Error("Wrong Size for Palette");
					break;
				case 1146114131://DPPS (Deluxe Paint III perspective)
					//if(partSize == 110){
						//Log Passing Over Data.(type and Size info here)
						reader->SetOffset((reader->GetOffset()+partSize));
					//}

					break;
				case 1129467463://CRNG (animation info)
					if(partSize == 8){
						if(animationCount < 16){
							this->animationData[animationCount] = NULL;
							animationCount++;
						}
						else
							LOGSYSTEM->Error("Extra Animation Data");
					}
					else
						LOGSYSTEM->Error("Wrong Size for Animation Data " + Functions::ToString((int)animationCount));
					break;
				case 1414090329://TINY (preview image)
					if(this->pictureHeader != NULL){// if Preview Image Before Header

					}
					break;
				case 1112491097://BODY (IMAGE Data (chars))
					if(this->pictureHeader != NULL){// if Image Data Before Header

					}
					break;
				default:
					//skip the section
					//Log Passing Over Data. (type and Size info here)
					reader->SetOffset((reader->GetOffset()+partSize));
					break;
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

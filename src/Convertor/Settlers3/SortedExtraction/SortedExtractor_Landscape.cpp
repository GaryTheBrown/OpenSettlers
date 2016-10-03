//============================================================================
// Name        : SortedExtractor_Landscape.cpp
// Author      : Gary_The_Brown
// Copyright   :
// Description :
//============================================================================

#include "../SortedExtractor.h"

namespace Extractor {
	namespace Settlers3{
		void SortedExtractor::Landscape(){
/*			std::string file = this->fileData->GFX->FileReturn("3_00.");
			if(file != ""){
				std::string location = this->extractionLocation + this->extractionLocationGFX + this->extractionLocationLandscape;
				Functions::CreateDir(location);
				DataFile* imageFile = new DataFile(this->locationofGFXFiles + this->fileData->GFX->folder + file);
				//235 files 0-234
				for (unsigned char i = 0; i < 235; i++){
					imageFile->ReturnLandscapeImage(i)->SaveToRGBBMP(location + Functions::ToString((int)i));
				}
				delete imageFile;
			}
			*/
		}
	}
}

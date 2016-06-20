//============================================================================
// Name        : LBMPalette.cpp
// Author      : Gary_The_Brown
// Description :
//============================================================================

#include "LBMPalette.h"

namespace Extractor {
	namespace Settlers2{
		LBMPalette::LBMPalette(Functions::DataReader* reader) {

			for(unsigned short i = 0; i < 256; i++){
				this->palette[i].R = reader->ReadChar();
				this->palette[i].G = reader->ReadChar();
				this->palette[i].B = reader->ReadChar();
			}
		}

		LBMPalette::~LBMPalette() {

		}
	}
}

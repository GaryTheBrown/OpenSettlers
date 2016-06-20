//============================================================================
// Name        : LBMAnimationData.cpp
// Author      : Gary_The_Brown
// Description :
//============================================================================

#include "LBMAnimationData.h"

namespace Extractor {
	namespace Settlers2{

	LBMAnimationData::LBMAnimationData(Functions::DataReader* reader) {

			this->flags = reader->ReadShort();
			this->rate = reader->ReadShort();

			this->padding = reader->ReadShort();
			this->low = reader->ReadChar();
			this->high = reader->ReadChar();
		}

	LBMAnimationData::~LBMAnimationData() {

		}
	}
}

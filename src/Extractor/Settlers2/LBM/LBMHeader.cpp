//============================================================================
// Name        : LBMHeader.cpp
// Author      : Gary_The_Brown
// Description :
//============================================================================

#include "LBMHeader.h"

namespace Extractor {
	namespace Settlers2{

		LBMHeader::LBMHeader(Functions::DataReader* reader) {
			this->chunkID = reader->ReadInt();
			this->lenChunk = reader->ReadInt();
			this->formatID = reader->ReadInt();
		}

		LBMHeader::~LBMHeader() {

		}
	}
}

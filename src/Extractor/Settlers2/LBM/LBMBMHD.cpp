//============================================================================
// Name        : LBMBMHD.cpp
// Author      : Gary_The_Brown
// Description :
//============================================================================

#include "LBMBMHD.h"

namespace Extractor {
	namespace Settlers2{
		LBMBMHD::LBMBMHD(Functions::DataReader* reader) {
			this->width = reader->ReadShort();
			this->height = reader->ReadShort();
			this->xOrigin = reader->ReadShort();
			this->yOrigin = reader->ReadShort();
			this->numPlanes = reader->ReadChar();
			this->mask = reader->ReadChar();
			this->compression = reader->ReadChar();
			this->pad1 = reader->ReadChar();
			this->transClr = reader->ReadShort();
			this->xAspect = reader->ReadChar();
			this->yAspect = reader->ReadChar();
			this->pageWidth = reader->ReadShort();
			this->pageHeight = reader->ReadShort();
		}

		LBMBMHD::~LBMBMHD() {

		}
	}
}

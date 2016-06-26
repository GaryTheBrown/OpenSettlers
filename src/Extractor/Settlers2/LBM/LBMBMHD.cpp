/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

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

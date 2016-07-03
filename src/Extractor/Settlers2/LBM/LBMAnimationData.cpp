/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "LBMAnimationData.h"

namespace Extractor {
	namespace Settlers2{

		LBMAnimationData::LBMAnimationData(Functions::DataReader* reader) {

			this->flags = reader->ReadShort();
			this->rate = reader->ReadShort();
			this->padding = reader->ReadShort();

			this->active = ((this->flags & 1) >= 1);
			this->direction = (((this->flags >> 1) & 1) >= 1);

			this->low = reader->ReadChar();
			this->high = reader->ReadChar();

		}

		LBMAnimationData::~LBMAnimationData() {

		}

		std::string LBMAnimationData::ToString(){
			std::string data = "";
			data += Functions::ToString((int)this->padding);
			data += " \t" + Functions::ToString((int)this->rate);
			data += " \t" + Functions::ToString((int)this->flags);
			data += " \t" + Functions::ToString((int)this->low);
			data += " \t" + Functions::ToString((int)this->high);
			data += " \t";
			data += (this->active?"true":"false");
			data += " \t";
			data += (this->direction?"true":"false");
			data += "\n";
			return data;
		}
	}
}

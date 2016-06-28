/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <string>
#include "../../../../Log.h"
#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/File/Save.h"
#include "../../../../Functions/To.h"
#include "../MAPParts.h"
#include "../../Lists/Goods.h"

namespace Extractor{
	namespace Settlers3{
		class MAPGoods : public MAPParts{
		public:
			struct Good{
				short x_pos;
				short y_pos;
				char type;
				char count;
				char unknown1;
				char unknown2;
			};
		private:
			unsigned int goodsCount;
			Good* goods;
		public:
			MAPGoods(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey);
			virtual ~MAPGoods();
			virtual std::string HeaderToString();
			void SaveFileData(std::string location);
		};
	}
}

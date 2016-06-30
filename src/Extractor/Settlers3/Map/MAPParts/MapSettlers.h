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
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/File/Save.h"
#include "../../../../Functions/To.h"
#include "../MAPParts.h"
#include "../../Lists/Settlers.h"

namespace Extractor{
	namespace Settlers3{
		class MAPSettlers : public MAPParts{
		public:
			struct Settler{
				char player;
				char type;
				short x_pos;
				short y_pos; //(-1?)
			};
		private:
			unsigned int settlerCount;
			Settler* settlers;
		public:
			MAPSettlers(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey);
			virtual ~MAPSettlers();
			virtual std::string HeaderToString();
			void SaveFileData(std::string location);
		};
	}
}

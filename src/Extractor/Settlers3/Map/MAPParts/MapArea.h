//============================================================================
// Name        : MAPArea.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPAREA_H_
#define EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPAREA_H_

#include <string>
#include "../../../../Log.h"
#include "../../../../LogSystem/LogSystem.h"
#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/FileSave.h"
#include "../../../../Functions/OutputVar.h"
#include "../MAPParts.h"

namespace Extractor{
	namespace Settlers3{
		class MAPArea: public MAPParts{
		public:
			struct MapTile{
				unsigned char height = 0;
				unsigned char type = 0;
				unsigned char object = 0;
				unsigned char playerClaim = 0;
				unsigned char accessible = 0;
				unsigned char resources = 0;
			};
		private:
			//Map Info
			int mapSizeHeight = 0;
			int mapSizeWidth = 0;
			MapTile* mapData = NULL;

		public:
			MAPArea(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey);
			virtual ~MAPArea();
			virtual std::string HeaderToString();
			void SaveFileData(std::string location);


			int MapSizeHeight(){return this->mapSizeHeight;};
			int MapSizeWidth(){return this->mapSizeWidth;};
			MapTile* MapData(){return this->mapData;}
		};
	}
}
#endif

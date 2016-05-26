//============================================================================
// Name        : MAPInfo.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPINFO_H_
#define EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPINFO_H_

#include <string>
#include "../../../../Log.h"
#include "../../../../LogSystem/LogSystem.h"

#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/OutputVar.h"
#include "../MAPParts.h"
namespace Extractor{
	namespace Settlers3{
		class MAPInfo: public MAPParts{
		public:
			enum enumStartResources{
				startResourceLow = 1,
				startResourcesNormal = 2,
				startResourcesHigh = 3
			};

		private:

			//Map Info
			bool isSinglePlayerMap = true; //offset:00(4)
			int playerCount = 0; //offset:04(4)
			enumStartResources startResources = startResourcesNormal; //offset:08(4)
			//offset:12 to 24 EMPTY (Always Zero)


		public:
			MAPInfo(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey);
			virtual ~MAPInfo();
			virtual std::string ToString();

			bool IsSinglePlayerMap(){return this->isSinglePlayerMap;};
			int PlayerCount(){return this->playerCount;};
			enumStartResources StartResources(){return this->startResources;};
		};
	}
}
#endif

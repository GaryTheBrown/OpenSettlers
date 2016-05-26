//============================================================================
// Name        : MAPVictoryConditions.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPVICTORYCONDITIONS_H_
#define EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPVICTORYCONDITIONS_H_

#include <string>
#include "../../../../Log.h"
#include "../../../../LogSystem/LogSystem.h"
#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/OutputVar.h"
#include "../MAPParts.h"
namespace Extractor{
	namespace Settlers3{
		class MAPVictoryConditions: public MAPParts{
		public:
			struct BuildingData{
				unsigned char playerNumber;
				unsigned char buildingType;
			};

			struct LocationData{
				bool enabled;
				unsigned short X;
				unsigned short Y;
			};
			struct GoodsData{
				unsigned short amount;
				unsigned char goodsType;
			};

		private:
			//Opponents
			bool victoryAnnihilatePlayers = false;
			bool victoryAnnihilatePlayersCount[20];
			//Buildings
			bool victoryDestroyBuilding = false;
			BuildingData victoryDestroyBuildingData[10];
			//Location
			bool victoryControlSpecialLocation = false;
			LocationData victoryControlLocationData[5];
			//Time
			bool victoryControlTime = false;
			unsigned short victoryControlTimeLength[20];
			//Goods
			bool victoryControlProduceGoods = false;
			GoodsData victoryControlProduceGoodsData[3];

			bool CharToBool(unsigned char value);

		public:
			MAPVictoryConditions(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey);
			virtual ~MAPVictoryConditions();
			virtual std::string ToString();
		};
	}
}
#endif

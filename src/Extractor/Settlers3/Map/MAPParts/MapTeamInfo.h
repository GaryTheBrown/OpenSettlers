//============================================================================
// Name        : MAPTeamInfo.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPTEAMINFO_H_
#define EXTRACTOR_SETTLERS3_MAP_MAPPARTS_MAPTEAMINFO_H_

#include <string>
#include "../../../../Log.h"
#include "../../../../LogSystem/LogSystem.h"

#include "../../../../Functions/DataReader.h"
#include "../../../../Functions/OutputVar.h"
#include "../MAPParts.h"
namespace Extractor{
	namespace Settlers3{
		class MAPTeamInfo: public MAPParts{
		public:
			enum enumControlType{
				ControlType_Choose = 0,
				ControlType_Human = 1,
				ControlType_Computer = 2
			};

			struct PlayerInfo{
				unsigned int Team;
				enumControlType controlType;
			};

		private:
			PlayerInfo* playerInfo;
			unsigned int playerCount;

		public:
			MAPTeamInfo(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey, unsigned int playerCount);
			virtual ~MAPTeamInfo();
			virtual std::string ToString();
		};
	}
}
#endif

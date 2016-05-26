//============================================================================
// Name        : MAPPlayerInfo.cpp
// Author      : Gary_The_Brown
// Description :
//============================================================================

#include "MapPlayerInfo.h"

namespace Extractor{
	namespace Settlers3{
		MAPPlayerInfo::MAPPlayerInfo(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey, unsigned int playerCount):MAPParts(reader,offset,size,cryptKey,false) {

			if(this->hasBeenDecrypted){

				if (this->size == 0){
					LOGSYSTEM->Error("No player information available in Map File!");
					return;
				}

				this->playerCount = playerCount;

				this->playerInfo = new PlayerInfo[this->playerCount];

				for (unsigned int i = 0; i < this->playerCount; i++){
					this->playerInfo[i].armyType = reader->ReadInt();
					this->playerInfo[i].locationX = reader->ReadInt();
					this->playerInfo[i].locationY = reader->ReadInt();

					char nextLetter = reader->ReadChar();
					for (unsigned int j = 0; j < 32; j++){
						if (nextLetter != 0x00)
							this->playerInfo[i].name += nextLetter;
						nextLetter = reader->ReadChar();
					}
				}
			}
			else{
				//decryption failed
				LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
			}
		}

		MAPPlayerInfo::~MAPPlayerInfo() {
			delete [] this->playerInfo;
		}

		std::string MAPPlayerInfo::ToString(){

			if (this->hasBeenDecrypted == false)
				return MAPParts::HeaderToString();

			std::string returnString;

			for (unsigned int i = 0; i < this->playerCount; i++){
				returnString += "Player (" + Functions::ToString(i) + ")\n";
				returnString += "\tArmyType=";
				switch(this->playerInfo[i].armyType){
				case 0:
					returnString += "Roman";
					break;
				case 1:
					returnString += "Egyptian";
					break;
				case 2:
					returnString += "Asian";
					break;
				case 3:
					returnString += "Amazon";
					break;
				case 4:
					returnString += "choice";
					break;
				default:
					returnString += "Unknown";
					break;
				}
				returnString += "\n";
				returnString += "\tLocation=" + Functions::ToString(this->playerInfo[i].locationX) + "," + Functions::ToString(this->playerInfo[i].locationY) + "\n";
				returnString += "\tName=" + this->playerInfo[i].name + "\n";
			}
			return returnString;
		}
	}
}

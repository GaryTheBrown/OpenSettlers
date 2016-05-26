//============================================================================
// Name        : MAPTeamInfo.cpp
// Author      : Gary_The_Brown
// Description :
//============================================================================

#include "MapTeamInfo.h"

namespace Extractor{
	namespace Settlers3{
		MAPTeamInfo::MAPTeamInfo(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey, unsigned int playerCount):MAPParts(reader,offset,size,cryptKey,false) {

			if(this->hasBeenDecrypted){

				if (this->size == 0){
					LOGSYSTEM->Error("No player information available in Map File!");
					return;
				}

				reader->SetOffset(offset + 33);

				this->playerCount = playerCount;

				this->playerInfo = new PlayerInfo[this->playerCount];

				for (unsigned int i = 0; i < this->playerCount; i++){
					//Get Team Number
					this->playerInfo[i].Team = reader->ReadChar();
					// Get Control Type
					char tmp = reader->ReadChar();
					switch(tmp){
					default:
					case 0:
						this->playerInfo[i].controlType = ControlType_Choose;
						break;
					case 1:
						this->playerInfo[i].controlType = ControlType_Human;
						break;
					case 2:
						this->playerInfo[i].controlType = ControlType_Computer;
						break;
					}

				}
			}
			else{
				//decryption failed
				LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
			}
		}

		MAPTeamInfo::~MAPTeamInfo() {
			delete [] this->playerInfo;
		}

		std::string MAPTeamInfo::ToString(){

			if (this->hasBeenDecrypted == false)
				return MAPParts::HeaderToString();

			std::string returnString;

			for (unsigned int i = 0; i < this->playerCount; i++){
				returnString += "Player (" + Functions::ToString(i) + ")\n";
				returnString += "\tTeam=" + Functions::ToString(this->playerInfo[i].Team) + "\n";
				returnString += "\tControlType=";
				switch(this->playerInfo[i].controlType){
				case ControlType_Choose:
					returnString += "Choose";
					break;
				case ControlType_Human:
					returnString += "Human";
					break;
				case ControlType_Computer:
					returnString += "Computer";
					break;
				default:
					returnString += "Unknown";
					break;
				}
				returnString += "\n";
			}
			return returnString;
		}
	}
}

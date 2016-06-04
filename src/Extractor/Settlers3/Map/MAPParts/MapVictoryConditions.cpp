/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MapVictoryConditions.h"

namespace Extractor{
	namespace Settlers3{

		bool MAPVictoryConditions::CharToBool(unsigned char value){
			if(value == 1)
				return true;
			return false;
		}

		MAPVictoryConditions::MAPVictoryConditions(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey):MAPParts(reader,offset,size,cryptKey,false) {

			if(this->hasBeenDecrypted){

				if (this->size == 0){
					LOGSYSTEM->Error("No player information available in Map File!");
					return;
				}

				//Opponents
				this->victoryAnnihilatePlayers = this->CharToBool(reader->ReadChar());
				for (unsigned char i = 0; i < 20; i++){
					this->victoryAnnihilatePlayersCount[i] = this->CharToBool(reader->ReadChar());
				}

				//Buildings
				this->victoryDestroyBuilding = this->CharToBool(reader->ReadChar());
				for (unsigned char i = 0; i < 10; i++){
					this->victoryDestroyBuildingData[i].playerNumber = reader->ReadChar();
					this->victoryDestroyBuildingData[i].buildingType = reader->ReadChar();
				}

				//Location
				this->victoryControlSpecialLocation = this->CharToBool(reader->ReadChar());
				for (unsigned char i = 0; i < 5; i++){
					this->victoryControlLocationData[i].enabled = this->CharToBool(reader->ReadChar());
					this->victoryControlLocationData[i].X = reader->ReadShort();
					this->victoryControlLocationData[i].Y = reader->ReadShort();
				}

				//Time
				this->victoryControlTime = this->CharToBool(reader->ReadChar());
				for (unsigned char i = 0; i < 20; i++){
					this->victoryControlTimeLength[i] = reader->ReadShort();
				}

				//Goods
				this->victoryControlProduceGoods = this->CharToBool(reader->ReadChar());
				for (unsigned char i = 0; i < 3; i++){
					this->victoryControlProduceGoodsData[i].amount = reader->ReadShort();
					this->victoryControlProduceGoodsData[i].goodsType = reader->ReadChar();
				}
			}
			else{
				//decryption failed
				LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
			}
		}

		MAPVictoryConditions::~MAPVictoryConditions() {
		}

		std::string MAPVictoryConditions::ToString(){

			if (this->hasBeenDecrypted == false)
				return MAPParts::HeaderToString();

			std::string returnString;
			returnString += "VictoryAnnihilatePlayers=";
			returnString += (this->victoryAnnihilatePlayers?"True":"False");
			returnString += "\n";

			for (unsigned char i = 0; i < 20; i++){
				returnString += "\tPlayer(";
				returnString += Functions::ToString((int)i+1);
				returnString += ")=";
				returnString += (this->victoryAnnihilatePlayersCount[i]?"True":"False");
				returnString += "\n";
			}

			returnString += "VictoryDestroyBuilding=";
			returnString += (this->victoryDestroyBuilding?"True":"False");
			returnString += "\n";
			for (unsigned char i = 0; i < 10; i++){
				returnString += "\tPlayerNumber=";
				returnString += Functions::ToString((int)this->victoryDestroyBuildingData[i].playerNumber);
				returnString += "\n";
				//Change to text
				returnString += "\tBuildingType=";
				returnString += BuildingsList[this->victoryDestroyBuildingData[i].buildingType];
				returnString += "\n";
			}

			returnString += "VictoryControlSpecialLocation=";
			returnString += (this->victoryControlSpecialLocation?"True":"False");
			returnString += "\n";
			for (unsigned char i = 0; i < 5; i++){
				returnString += "\tEnabled=";
				returnString += (this->victoryControlLocationData[i].enabled?"True":"False");
				returnString += "\n";
				returnString += "\tLocationX=";
				returnString += Functions::ToString(this->victoryControlLocationData[i].X);
				returnString += "\n";
				returnString += "\tLocationY=";
				returnString += Functions::ToString(this->victoryControlLocationData[i].Y);
				returnString += "\n";
			}

			returnString += "VictoryControlTime=";
			returnString += (this->victoryControlTime?"True":"False");
			returnString += "\n";
			for (unsigned char i = 0; i < 20; i++){
				returnString += "\tLength(Player[";
				returnString += Functions::ToString((int)i+1);
				returnString += "])=";
				returnString += Functions::ToString(this->victoryControlTimeLength[i]);
				returnString += "\n";
			}

			returnString += "VictoryControlTime=";
			returnString += (this->victoryControlProduceGoods?"True":"False");
			returnString += "\n";
			for (unsigned char i = 0; i < 3; i++){
				returnString += "\tAmount=";
				returnString += Functions::ToString(this->victoryControlProduceGoodsData[i].amount);
				returnString += "\n";
				//change to text
				returnString += "\tGoodsType=";
				returnString += Functions::ToString(ResourcesList[this->victoryControlProduceGoodsData[i].goodsType]);
				returnString += "\n";
			}

			return returnString;
		}
	}
}

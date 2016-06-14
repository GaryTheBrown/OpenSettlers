/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MapGoods.h"

namespace Extractor{
	namespace Settlers3{
		MAPGoods::MAPGoods(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey):MAPParts(reader,offset,size,cryptKey,false){

			if(this->hasBeenDecrypted){

				if (this->size == 0){
					LOGSYSTEM->Error("No area-information available in mapfile!");
					return;
				}
				//- height and width are the same
				this->goodsCount = reader->ReadInt();

				this->goods = new Good[this->goodsCount];

				for (unsigned int i = 0; i < this->goodsCount; i++){


					this->goods[i].x_pos = reader->ReadShort();
					this->goods[i].y_pos = reader->ReadShort();
					this->goods[i].type = reader->ReadChar();
					this->goods[i].count = reader->ReadChar();
					this->goods[i].unknown1 = reader->ReadChar();
					this->goods[i].unknown2 = reader->ReadChar();
				}
			}
			else{
				//decryption failed
				LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
			}
		}

		MAPGoods::~MAPGoods(){
			delete [] this->goods;
		}

		std::string MAPGoods::HeaderToString(){

			if (this->hasBeenDecrypted == false)
				return MAPParts::HeaderToString();

			std::string returnString;
			returnString += "GOODSCOUNT=" + Functions::ToString(this->goodsCount) + "\n";

			for (unsigned int i = 0; i < this->goodsCount; i++){
				returnString += "Goods:" + Functions::ToString(i+1) + "\n";
				returnString += "\tX Pos=" + Functions::ToString((int)this->goods[i].x_pos) + "\n";
				returnString += "\tY Pos=" + Functions::ToString((int)this->goods[i].y_pos) + "\n";
				returnString += "\tType=" + GoodsList[(int)this->goods[i].type] + "\n";
				returnString += "\tCount=" + Functions::ToString((int)this->goods[i].count) + "\n";
				returnString += "\tUnknown1=" + Functions::ToString((int)this->goods[i].unknown1) + "\n";
				returnString += "\tUnknown2=" + Functions::ToString((int)this->goods[i].unknown2) + "\n";
			}
			return returnString;
		}

		void MAPGoods::SaveFileData(std::string location){

			Functions::SaveToTextFile(location + "/Goods.txt",this->HeaderToString());
		}
	}
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MapText.h"

namespace Extractor{
	namespace Settlers3{
		MAPText::MAPText(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey):MAPParts(reader,offset,size,cryptKey,false){

			if(this->hasBeenDecrypted){

				if (this->size == 0){
					LOGSYSTEM->Error("No player information available in Map File!");
					return;
				}

				char nextLetter = reader->ReadChar();
				while (nextLetter != 0x00){
					this->text += nextLetter;
					nextLetter = reader->ReadChar();
				}
			}
			else{
				//decryption failed
				LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
			}
		}

		std::string MAPText::ToString(){

			if (this->hasBeenDecrypted == false)
				return MAPParts::HeaderToString();

			return "Text=" + this->text + "\n";
		}
	}
}

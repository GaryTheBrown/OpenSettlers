/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "To.h"
namespace Functions{
	std::string ToHex(int value,int bytes){
		std::stringstream streamHex;
		streamHex << std::hex << std::setw(bytes*2)<<value << std::dec;
		return streamHex.str();
	}

	std::string ToBinary(int value,int bytes){
		if(bytes == 1){
			std::bitset<8> b(value);
			return b.to_string();
		}
		else if(bytes == 2){
			std::bitset<16> b(value);
			return b.to_string();
		}
		else if(bytes == 4){
			std::bitset<32> b(value);
			return b.to_string();
		}
		else if(bytes == 8){
			std::bitset<64> b(value);
			return b.to_string();
		}
		else
			return "";
	}
}

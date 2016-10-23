/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "To.h"

std::string Functions::ToHex(int value,int bytes){
	std::stringstream streamHex;
	streamHex << std::hex << std::setw(bytes*2)<<value << std::dec;
	return streamHex.str();
}

std::string Functions::ToBinary(int value,int bytes){
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

unsigned int Functions::StringToHex(std::string value){
	unsigned long temp;
	temp = std::stoul(value, nullptr, 16);
	return ((int) temp & 0xFFFFFFFF);
}

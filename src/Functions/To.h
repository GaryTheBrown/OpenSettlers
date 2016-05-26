/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_FUNCTIONS_TO_H_
#define EXTRACTOR_FUNCTIONS_TO_H_

#include <iostream>
#include <iomanip>
#include <bitset>
#include<sstream>
#include <string>
namespace Functions{
	template <typename T> std::string ToString(T value){
		std::ostringstream os;
		os << value ;
		return os.str() ;
	}
	extern std::string ToHex(int value,int bytes = 1);
	extern std::string ToBinary(int value,int bytes = 1);
}
#endif

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <iostream>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <string>

namespace Functions{
	template <typename T> std::string ToString(T value){
		std::ostringstream os;
		os << value ;
		return os.str() ;
	}
	extern std::string ToHex(int value,int bytes = 1);
	extern std::string ToBinary(int value,int bytes = 1);
	extern unsigned int StringToHex(std::string value);

	template <class T> std::string OutputVar(std::string varName, T varValue,int bytes = 1, bool full = true){
		std::string returnString;
		if(full){
			returnString += varName + "=\tDec:" + ToString((int)varValue);
			returnString += "\tBinary:" + ToBinary(varValue,bytes);
			returnString += "\tHex: 0x" + ToHex(varValue,bytes);
		}
		else
			returnString = varName + "=" + ToString(varValue);
		return returnString;
	}
}

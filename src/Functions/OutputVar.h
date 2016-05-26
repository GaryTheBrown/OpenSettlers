/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_FUNCTIONS_OutputVar_H_
#define EXTRACTOR_FUNCTIONS_OutputVar_H_
#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>
#include "To.h"
namespace Functions{
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
#endif

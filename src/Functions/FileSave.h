/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_FUNCTIONS_FILESAVE_H_
#define EXTRACTOR_FUNCTIONS_FILESAVE_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "To.h"
#include "FileFunctions.h"

namespace Functions{
	extern void SaveToTextFile(std::string FileLocation,std::string Data);
	extern void SaveToBinaryFile(std::string FileLocation,char* Data,unsigned int size);
}
#endif

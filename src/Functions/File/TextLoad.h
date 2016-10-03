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
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <iterator>
#include <iostream>
#include <algorithm>

namespace Functions{
	extern std::vector<std::pair<std::string,std::string>>* LoadFromTextFile(std::string file);
	extern std::vector<std::pair<std::string,std::string>>* LoadFromTextLine(std::string line);
	extern std::vector<std::pair<std::string,std::string>>* TextLinesToList(std::vector<std::string>* lines, char deliminator);
}

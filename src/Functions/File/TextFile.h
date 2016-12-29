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

#include <fstream>
#include <string>
#include <vector>

namespace Functions{
	extern std::vector<std::pair<std::string,std::string>>* LoadVariablesFromTextFile(std::string file);
}

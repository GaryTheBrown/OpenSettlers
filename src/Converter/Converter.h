/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef CONVERTER_CONVERTER_H
#define CONVERTER_CONVERTER_H

#include <string>
#include "../Log.h"
#include "../Functions/File/Functions.h"
#include "../OSDataFile/FileTypes/GameType.h"

//#include "Settlers1/Convert.h"
//#include "Settlers2/Convert.h"
#include "Settlers3/Convert.h"
//#include "Settlers4/Convert.h"

namespace Converter{
	extern bool Main(std::string location, std::string saveLocation);
}

#endif
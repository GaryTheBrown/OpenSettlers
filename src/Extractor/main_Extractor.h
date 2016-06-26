/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <string>
#include <vector>
#include "eType.h"
#include "../Log.h"
#include "../Functions/File/Functions.h"
#include "../Functions/DataReader.h"
//#include "Settlers1/Extractor.h"
#include "Settlers2/Extractor.h"
#include "Settlers3/Extractor.h"
//#include "Settlers4/Extractor.h"

namespace Extractor{
		extern bool Main(std::string location);
}

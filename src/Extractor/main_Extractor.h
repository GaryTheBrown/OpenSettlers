/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_MAIN_H_
#define EXTRACTOR_MAIN_H_

#include <string>
#include "eType.h"
#include "../Log.h"
#include "../Functions/FileFunctions.h"
#include "../Functions/DataReader.h"
#include "Settlers3/Extractor.h"

namespace Extractor{
		extern bool Main(std::string location, eType type);
		extern bool FULLRAW(std::string location, char gameNo, bool GOG);
}
#endif

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "RemoveFolder.h"

namespace Functions {
	void RemoveFolder(std::string folder){
		//LINUX ONLY
		std::string command = "rm -r " + folder;
		system(command.c_str());
	}
}

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
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <vector>

namespace Functions{
	extern bool FileExists(std::string file);
	extern bool FolderExists(std::string folder);
	extern void CreateDir(std::string FileName);
	extern void Copy(std::string from, std::string to);
	extern void RemoveFolder(std::string folder);
	extern std::vector<std::string> GetDir(std::string directory);
}

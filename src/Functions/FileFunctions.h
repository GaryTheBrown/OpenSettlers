/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_FUNCTIONS_FILEFUNCTIONS_H_
#define EXTRACTOR_FUNCTIONS_FILEFUNCTIONS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

namespace Functions{
	extern bool FileExists(std::string file);
	extern bool FolderExists(std::string folder);
	extern void CreateDir(std::string FileName);
	extern void Copy(std::string from, std::string to);
}
#endif

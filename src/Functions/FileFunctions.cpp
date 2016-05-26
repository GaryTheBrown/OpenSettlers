/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "FileFunctions.h"

namespace Functions{
	bool FileExists(std::string file){
		std::ifstream ifile(file.c_str());
		if (ifile.is_open() == false)
			return false;
		ifile.close();
		return true;
	}

	bool FolderExists(std::string folder){
		struct stat info;
		if((stat(folder.c_str(), &info ) != 0)||!(info.st_mode & S_IFDIR))
			return false;
		return true;
	}

	void CreateDir(std::string FileName){
		if(FolderExists(FileName) == false){
			std::string command = "mkdir " + FileName;
			system(command.c_str());
		}
	}

	void Copy(std::string from, std::string to){
	     std::ifstream source(from, std::ios::binary);
	     std::ofstream destination(to, std::ios::binary);
	     destination << source.rdbuf();
	}
}

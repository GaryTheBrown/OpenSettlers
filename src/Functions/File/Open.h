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
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <algorithm>
#include <iomanip>
#include <string>

namespace Functions{
	class File{
	private:
		char* fileBuffer = NULL;
		char* tmpBuffer = NULL; //For Odd Offsets
		unsigned int fileSize = 0;
		std::string file;
		std::string fileName;
		std::string fileExt;

	public:
		File(std::string file);
		~File();

		const char* FetchBuffer(unsigned int offset,unsigned int size);
		const char *readBuffer(int offset);


		unsigned int FileSize(){return this->fileSize;};
		std::string FullFileName(){return this->file;};
		std::string FileName(){return this->fileName;};
		std::string FileExt(){return this->fileExt;};
		void DeleteTmpBuffer(){delete[] this->tmpBuffer;}
	};
}

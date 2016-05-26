/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "FileSave.h"
namespace Functions{
	void SaveToTextFile(std::string FileLocation,std::string Data){
		if (FileExists(FileLocation))
			remove(FileLocation.c_str());

		std::ofstream ofile;
		ofile.open(FileLocation.c_str());
		ofile.write(Data.c_str(),Data.length());
		ofile.close();
	}

	void SaveToBinaryFile(std::string FileLocation,char* Data,unsigned int size){
		if (FileExists(FileLocation))
			remove(FileLocation.c_str());

		std::ofstream ofile;
		ofile.open(FileLocation.c_str(), std::ios::binary);
		ofile.write(Data,size);
		ofile.close();
	}
}

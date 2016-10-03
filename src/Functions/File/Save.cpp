/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Save.h"

void Functions::SaveToTextFile(std::string fileLocation,std::string data){
	if (FileExists(fileLocation))
		remove(fileLocation.c_str());

	std::ofstream ofile;
	ofile.open(fileLocation.c_str());
	ofile.write(data.c_str(),data.length());
	ofile.close();
}

void Functions::SaveToBinaryFile(std::string fileLocation,char* data,unsigned int size){
	if (FileExists(fileLocation)) remove(fileLocation.c_str());

	std::ofstream ofile;
	ofile.open(fileLocation.c_str(), std::ios::binary);
	ofile.write(data,size);
	ofile.close();
}

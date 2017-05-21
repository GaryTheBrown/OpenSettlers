/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "TextFile.h"

namespace Functions{
	std::vector<std::pair<std::string,std::string>>* LoadVariablesFromTextFile(std::string file){

		std::vector<std::pair<std::string,std::string>>* data = new std::vector<std::pair<std::string,std::string>>();
		std::vector<std::string>* lines = new std::vector<std::string>();
		std::string singleLine;

		//open the ifile.
		std::ifstream iFile(file.c_str());

		//loop through lines in file and fill a list
		while(std::getline(iFile, singleLine, '\n')) {
			lines->push_back(singleLine);
		}

		//close ifile
		iFile.close();

		for(auto line=lines->begin() ; line < lines->end(); line++ ){
			size_t pos;
			pos = line->find_first_of('=');
			data->push_back(std::make_pair(line->substr(0, pos),line->substr(pos+1)));
		}
		lines->clear();
		delete lines;
		return data;
	}
}

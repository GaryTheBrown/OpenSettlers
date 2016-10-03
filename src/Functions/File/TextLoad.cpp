/*
 * LoadFunctions.h
 *
 *  Created on: 8 Oct 2014
 *      Author: gary
 */

#include "TextLoad.h"

namespace Functions{
std::vector<std::pair<std::string,std::string>>* LoadFromTextFile(std::string file){

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

		return TextLinesToList(lines,'=');
	}

std::vector<std::pair<std::string,std::string>>* LoadFromTextLine(std::string line){

	std::vector<std::string>* lines = new std::vector<std::string>();
		std::string setting;

		std::istringstream buf(line);
		while(std::getline(buf, setting, ',')) {

			lines->push_back(setting);
		}

		return TextLinesToList(lines,':');

	}

std::vector<std::pair<std::string,std::string>>* TextLinesToList(std::vector<std::string>* lines, char deliminator){


		std::vector<std::pair<std::string,std::string>>* loadDataList = new std::vector<std::pair<std::string,std::string>>();

		for(unsigned int i = 0; i < lines->size(); i++){
			std::pair<std::string,std::string> loadData;
			size_t pos = lines->at(i).find_first_of(deliminator);
			loadData.first = lines->at(i).substr(0, pos);
			loadData.second = lines->at(i).substr(pos+1);
			loadDataList->push_back(loadData);
		}
		delete lines;
		return loadDataList;
	}
}

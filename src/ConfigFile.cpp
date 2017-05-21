/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "ConfigFile.h"

ConfigFile::ConfigFile(std::string file){
	if (file != "")
		this->location = file;
	else
		this->location = this->DEFAULT_Location;

	if (Functions::FileExists(this->location) == false){
		if (file != ""){
			LOGSYSTEM->Error("Config File " + this->location + " not Found");
			this->fileOK = false;
		}
		return;
	}

	std::vector<std::pair<std::string,std::string>>* data = Functions::LoadVariablesFromTextFile(this->location);

	for (auto line=data->begin() ; line < data->end(); line++ ){
		std::transform(line->first.begin(), line->first.end(), line->first.begin(), toupper);
		//Values here
		if (line->first == "FULLSCREEN"){
			this->fullscreen = true;
		} else if (line->first == "WINDOWSIZE"){
			std::size_t pos = line->second.find(",");
			this->windowSize.first = atoi(line->second.substr(0,pos).c_str());
			this->windowSize.second = atoi(line->second.substr(pos+1).c_str());
		}
	}


}

ConfigFile::~ConfigFile() {
	if ((this->fileOK)&&(this->configChanged)){
		std::string data = "#OpenSettlers Config\n";

		if (this->fullscreen != this->DEFAULT_Fullscreen){
			data += "Fullscreen=true\n";
		}

		if (this->windowSize != this->DEFAULT_WindowSize){
			data += "WindowSize=" + Functions::ToString(this->windowSize.first) + "," + Functions::ToString(this->windowSize.second) + "\n";
		}

		Functions::SaveToTextFile(this->location,data);
	}
}

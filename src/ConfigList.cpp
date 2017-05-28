/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "ConfigList.h"

ConfigList::ConfigList(){
//Fullscreen
	this->configList.push_back(dynamic_cast<ConfigTemplateBase*>(new ConfigTemplate<bool>("fullscreen","FullScreen",ConfigTemplateBase::cDisplay,false,ConfigTemplate<bool>::eBool)));
//Window Size
	unsigned int windowCount = 4;
	std::pair<std::string,std::pair<int,int>> *data = new std::pair<std::string,std::pair<int,int> >[windowCount];
	data[0] = std::make_pair("640x480",std::make_pair(640,480));
	data[1] = std::make_pair("800x600",std::make_pair(800,600));
	data[2] = std::make_pair("1024x768",std::make_pair(1024,768));
	data[3] = std::make_pair("1366x768",std::make_pair(1366,768));
	this->configList.push_back(dynamic_cast<ConfigTemplateBase*>(new ConfigTemplate<std::pair<int,int> >("windowsize","Window Size",ConfigTemplateBase::cDisplay,std::make_pair(800,600),windowCount, data)));

//list options here
}

ConfigList::~ConfigList() {
	for (unsigned int i = 0; i < this->configList.size(); i++ )
    {
        delete this->configList[i];
    }
    this->configList.clear();
}

bool ConfigList::ConfigFile(std::string file){
	if (Functions::FileExists(file) == false){
		if (file != ""){
			LOGSYSTEM->Error("Config File " + file + " not Found");
		}
		return false;
	}

	std::vector<std::pair<std::string,std::string> >* data = Functions::LoadVariablesFromTextFile(file);

	for (auto line=data->begin() ; line < data->end(); line++ ){
		if(this->OptionExists(line->first)){
			if(line->first == "fullscreen"){
				this->SetValue("fullscreen",true);
			}else if(line->first == "windowsize"){
				std::size_t pos = line->second.find(",");
				std::pair<int,int> pair = std::make_pair(atoi(line->second.substr(0,pos).c_str()),atoi(line->second.substr(pos+1).c_str()));
				this->SetValue("windowsize",pair);
			}
		}else{
			LOGSYSTEM->Error("Config Code " + line->first + "Not Found");
			return false;
		}
	}
	return true;
}


ConfigTemplateBase* ConfigList::GetConfigOptionBase(std::string code){
	for(auto item = this->configList.begin(); item != this->configList.end(); item++) {
		if ((*item)->CheckCode(code)){
			return (*item);
		}
	}
	return NULL;
}
bool ConfigList::OptionExists(std::string code){
	for(auto item = this->configList.begin(); item != this->configList.end(); item++) {
		if ((*item)->CheckCode(code)) return true;
	}
	return false;
}

template <typename T> T ConfigList::GetValue(std::string code){
	ConfigTemplateBase* option = this->GetConfigOptionBase(code);
	ConfigTemplate<T>* returnOption = static_cast<ConfigTemplate<T>*>(option);
	T returnValue = returnOption->GetValue();
	return returnValue;
}

template <typename T> void ConfigList::SetValue(std::string code,T value){
	ConfigTemplateBase* option = this->GetConfigOptionBase(code);
	ConfigTemplate<T>* returnOption = static_cast<ConfigTemplate<T>*>(option);
	returnOption->SetValue(value);
}

template <typename T> T ConfigList::GetConfigOption(std::string code){
						ConfigTemplateBase* option = this->GetConfigOptionBase(code);
						ConfigTemplate<T>* returnOption = static_cast<ConfigTemplate<T> *>(option);
						return returnOption;
}

void ConfigList::AddConfigOption(ConfigTemplateBase* configTemplateBase){
	this->configList.push_back(configTemplateBase);
}

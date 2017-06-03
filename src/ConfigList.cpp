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
	this->configList.push_back(dynamic_cast<ConfigTemplateBase*>(new ConfigTemplate<bool>("fullscreen","FullScreen",ConfigTemplateBase::cDisplay,false,ConfigTemplateBase::eBool)));
//Window Size
	unsigned int windowCount = 4;
	std::pair<std::string,std::pair<int,int> > *data = new std::pair<std::string,std::pair<int,int> >[windowCount];
	data[0] = std::make_pair("640x480",std::make_pair(640,480));
	data[1] = std::make_pair("800x600",std::make_pair(800,600));
	data[2] = std::make_pair("1024x768",std::make_pair(1024,768));
	data[3] = std::make_pair("1366x768",std::make_pair(1366,768));
	this->configList.push_back(dynamic_cast<ConfigTemplateBase*>(new ConfigTemplate<std::pair<int,int> >("windowsize","Window Size",ConfigTemplateBase::cDisplay,std::make_pair(800,600),windowCount, data)));
//FPS Options
	this->configList.push_back(dynamic_cast<ConfigTemplateBase*>(new ConfigTemplate<bool>("lockfps","Lock FPS",ConfigTemplateBase::cDisplay,true,ConfigTemplateBase::eBool)));
	this->configList.push_back(dynamic_cast<ConfigTemplateBase*>(new ConfigTemplate<bool>("showfps","Show FPS",ConfigTemplateBase::cDisplay,false,ConfigTemplateBase::eBool)));
	this->configList.push_back(dynamic_cast<ConfigTemplateBase*>(new ConfigTemplate<int>("maxfps","Max FPS",ConfigTemplateBase::cDisplay,30,ConfigTemplateBase::eInt)));
//list more options here
}

ConfigList::~ConfigList() {
	for (unsigned int i = 0; i < this->configList.size(); i++ ){
		delete this->configList[i];
	}
	this->configList.clear();
}
bool ConfigList::ConvertString(std::string first,std::string second){


	return false;
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
//Check If More than 1 Variable
			size_t pos = line->second.find_first_of(',');
			if (pos==std::string::npos){
				if(line->second == "true"){
					this->SetValue(line->first,true);
					return true;
				}
				if(line->second == "false"){
					this->SetValue(line->first,false);
					return true;
				}
				if((line->second[0] == '"')&&(line->second.back() == '"')){
					this->SetValue(line->first,line->second);
					return true;
				}
				if(atoi(line->second.c_str())){
					this->SetValue(line->first,atoi(line->second.c_str()));
					return true;
				}
				if(atof(line->second.c_str())){
					this->SetValue(line->first,atof(line->second.c_str()));
					return true;
				}

					return false;
			}
			std::string var1 = line->second.substr(0, pos);
			std::string var2 = line->second.substr(pos+1);

			if((atoi(var1.c_str()))&&(atoi(var2.c_str()))){
				auto pair = std::make_pair(atoi(var1.c_str()),(atoi(var2.c_str())));
				this->SetValue(line->first,pair);
				return true;
			}
		}
	}
	return false;
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

void ConfigList::AddConfigOption(ConfigTemplateBase* configTemplateBase){
	this->configList.push_back(configTemplateBase);
}

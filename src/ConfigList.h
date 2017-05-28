/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <string>
#include <utility>
#include <vector>
#include "ConfigTemplate.h"
#include "Functions/File/Functions.h"
#include "Functions/File/TextFile.h"
#include "Functions/File/Save.h"
#include "Functions/To.h"
#include "Log.h"

//TODO Need to Link this so a config file so it can set variables

//class holding a list
//constructor adds in options
//destructor cleans it up and is called at end of program
//Search and return a Config Option

//This class bellow will get the option it's loaded and then set it. ready for the game to access from a object that is passed into anywhere it's needed.
//Remove the vars from here and dynamically load them from file.

//Grouping needs to be thought about do I need it, will options menus always be created from set locations or will they have a dynamic way of being displayed..
class ConfigList {
	private:
		std::vector<ConfigTemplateBase*> configList;
	public:
		ConfigList();
		virtual ~ConfigList();

		bool ConfigFile(std::string file);
		bool OptionExists(std::string code);
		template <typename T> T GetValue(std::string code){
			auto optionBase =  this->GetConfigOptionBase(code);
			auto option = static_cast<ConfigTemplate<T>*>(optionBase) ;
			T value = option->GetValue();
			return value;
		};
		template <typename T> void SetValue(std::string code,T value){
			ConfigTemplateBase* option = this->GetConfigOptionBase(code);
			ConfigTemplate<T>* returnOption = static_cast<ConfigTemplate<T>*>(option);
			returnOption->SetValue(value);
		};
		ConfigTemplateBase* GetConfigOptionBase(std::string code);
		template <typename T> ConfigTemplate<T>* GetConfigOption(std::string code){
			ConfigTemplateBase* option = this->GetConfigOptionBase(code);
			ConfigTemplate<T>* returnOption = static_cast<ConfigTemplate<T> *>(option);
			return returnOption;
		};
		void AddConfigOption(ConfigTemplateBase* configTemplateBase);
};

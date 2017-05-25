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

template <class T> class ConfigTemplate{
	private:
		std::string code;
		std::string name;
		unsigned int value;
		unsigned int count;
		std::pair<std::string,T> *data;//string = Value to show, T is any value needed to store actual setting for use else where

	public:
		ConfigTemplate(std::string code, std::string name,unsigned int value, unsigned int count, std::pair<std::string,T> *data):code(code), name(name), value(value), count(count), data(data){}
		virtual ~ConfigTemplate(){delete[] data;}

		T GetDataValue(){return data[this->value].second;}
		T GetDataValue(int location){return data[location].second;}
		std::string GetTextValue(){return data[this->value].first;}
		std::string GetTextValue(int location){return data[location].first;}

		void SetValue(int setValue){this->value = setValue;}
		unsigned int GetValue(){return this->value;}
		bool CheckCode(std::string checkCode){if(this->code==checkCode)return true; else return false;}
};
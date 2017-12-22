/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <algorithm>
#include <string>
#include <utility>
#include <typeinfo>

class ConfigTemplateBase{
	public:
	enum eVarType : char{
		eBool = 0,
		eInt = 1,
		eString = 2,
	};

	enum configGroup : char{
		cGeneral = 0,
		cDisplay = 1,
		cAudio = 2,
		cLocation = 3,
	};

	protected:
		std::string code;
		std::string name;
		configGroup group;

	public:
		ConfigTemplateBase(){};
		ConfigTemplateBase(std::string code, std::string name,configGroup group = cGeneral):code(code),name(name),group(group){
			std::transform(this->code.begin(), this->code.end(),this->code.begin(), ::toupper);
		};
		virtual ~ConfigTemplateBase(){};

		const bool CheckCode(std::string checkCode){
			std::transform(checkCode.begin(), checkCode.end(),checkCode.begin(), ::toupper);
			if(this->code==checkCode)return true; else return false;}
		const std::string GetName(){return this->name;}
		const configGroup GetGroup(){return group;}
};

template <class T> class ConfigTemplate : public ConfigTemplateBase{
	public:

	private:
		T value;
		T defaultValue;
		unsigned int count;
		std::pair<std::string,T> *data = NULL;//string = Value to show, T is any value needed to store actual setting for use else where

	public:
		ConfigTemplate(){};
		ConfigTemplate(std::string code, std::string name, configGroup group, T defaultValue, unsigned int count, std::pair<std::string,T> *data):ConfigTemplateBase(code, name,group), value(defaultValue), defaultValue(defaultValue), count(count), data(data){}
		ConfigTemplate(std::string code, std::string name, configGroup group, T defaultValue,eVarType varType):ConfigTemplateBase(code, name, group), value(defaultValue), defaultValue(defaultValue){
			switch (varType){
				case eBool:{
					this->count = 2;
					this->data = new std::pair<std::string,T>[2];
					this->data[0] = std::make_pair("True",true);
					this->data[1] = std::make_pair("False",false);
					break;
				}
				case eInt:
				case eString:{
					this->count = 0;
					break;
				}
				default:
					break;
			}
		}


		virtual ~ConfigTemplate(){delete[] data;}

		const T GetValue(){return this->value;}
		const unsigned int GetCount(){return this->count;}
		const std::string GetTextValue(int location){return data[location].first;}
		const std::string GetTextValue(){
			for(unsigned int i = 0; i < this->count;i++){
				if (this->data[i].second == this->value){
					return data[i].first;
				}
			}
		}
		const T GetDataValue(int location){return data[location].second;}
		const T GetDataValue(std::string *name){
			for(unsigned int i = 0; i < this->count;i++){
				if (this->data[i].first == *name){
					return this->data[i].second;
				}
			}

		}

		void SetValue(T value){this->value = value;}
		bool SetFromDataValue(std::string *setValue){
			for(unsigned int i = 0; i < this->count;i++){
				if (this->data[i].first == *setValue){
					this->value = this->data[i].second;
					return true;
				}
			}
			return false;
		}
};
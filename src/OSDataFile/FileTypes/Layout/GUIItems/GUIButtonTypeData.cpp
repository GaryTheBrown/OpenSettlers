/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIButtonTypeData.h"

OSData::GUIButtonTypeData::GUIButtonTypeData(eType type)
	:type(type){
}

OSData::GUIButtonTypeData::GUIButtonTypeData(std::string type){
	this->GetButtonType(type);
}

OSData::GUIButtonTypeData::GUIButtonTypeData(eType type,std::string text)
	:type(type),text(text){
}

OSData::GUIButtonTypeData::GUIButtonTypeData(Functions::DataReader* reader){
	this->type = static_cast<eType>(reader->ReadChar());

	switch(this->type){
	case eNone:
	case eAction:
	default:
		break;
	case eChangeGlobalSetting:
	case eChangeSetting:
		unsigned char textSize = reader->ReadChar();
		this->text = reader->ReadString(textSize);
		break;
	}
}
OSData::GUIButtonTypeData::GUIButtonTypeData(xmlNode* node){//TODO MAKE HIS WORK

	if(node != NULL){

		xmlAttr* xmlAttribute = node->properties;
		while(xmlAttribute){
			this->CheckValues(((char*)xmlAttribute->name),((char*)xmlAttribute->children->content));
			xmlAttribute = xmlAttribute->next;
		}

//		xmlNode* itemNode = node->children;
//		while(itemNode){
//			this->CheckValues(((char*)itemNode->name),((char*)itemNode->content));
//			itemNode = itemNode->next;
//		}
	}
}
void OSData::GUIButtonTypeData::GetButtonType(std::string value){
	if (value == "None")
		this->type = eNone;
	else if(value == "Action")
		this->type = eAction;
	else if(value == "ChangeGlobalSetting")
		this->type = eChangeGlobalSetting;
	else if(value == "ChangeSetting")
		this->type = eChangeSetting;
}
std::string OSData::GUIButtonTypeData::ButtonTypeString(){
	if (this->type == eNone)
		return "None";
	else if(this->type == eAction)
		return "Action";
	else if(this->type == eChangeGlobalSetting)
		return "ChangeGlobalSetting";
	else if(this->type == eChangeSetting)
		return "ChangeSetting";

	return "None";
}
void OSData::GUIButtonTypeData::CheckValues(std::string name, std::string value){
	if (name == "Text")
		this->text = value;
	else if (name == "ButtonType")
			this->GetButtonType(value);
}
bool OSData::GUIButtonTypeData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;

	//Button Type(char)
	data->push_back(static_cast<char>(this->type));
	switch(this->type){
	case eNone:
	case eAction:
	default:
		break;
	case eChangeGlobalSetting:
	case eChangeSetting:
		//Text Size (char)
		unsigned short textSize = this->text.size();
		data->push_back(textSize & 0xFF);

		//Text (string)
		std::copy(this->text.begin(), this->text.end(), std::back_inserter(*data));
		break;
	}
	return true;
}

std::string OSData::GUIButtonTypeData::ToString(){
	std::string data;
	data += "GUIBUTTONTYPE\n";
	data += "Type = " + this->ButtonTypeString();

	switch(this->type){
	case eNone:
	case eAction:
	default:
		break;
	case eChangeGlobalSetting:
	case eChangeSetting:

		data += "Text = " + this->text + "\n";
		break;
	}
	return data;
}

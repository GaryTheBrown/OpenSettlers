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

OSData::GUIButtonTypeData::GUIButtonTypeData(eType type,std::string text,RGBA textColour,unsigned short fontSize)
	:type(type),text(text),	textColour(textColour), fontSize(fontSize){
}

OSData::GUIButtonTypeData::GUIButtonTypeData(Functions::DataReader* reader){
	this->type = static_cast<eType>(reader->ReadChar());

	switch(this->type){
	case eNone:
	case eAction:
	default:
		break;
	case eSwitchBool:
		unsigned char textSize = reader->ReadChar();
		this->text = reader->ReadString(textSize);
		this->textColour = reader->ReadInt();
		this->fontSize = reader->ReadShort();
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
	else if(value == "SwitchBool")
		this->type = eSwitchBool;
}
std::string OSData::GUIButtonTypeData::ButtonTypeString(){
	if (this->type == eNone)
		return "None";
	else if(this->type == eAction)
		return "Action";
	else if(this->type == eSwitchBool)
		return "SwitchBool";

	return "None";
}
void OSData::GUIButtonTypeData::CheckValues(std::string name, std::string value){
	if (name == "Text")
		this->text = value;
	else if (name == "TextColour")
		this->textColour = Functions::StringToHex(value);
	else if (name == "FontSize")
		this->fontSize = atoi(value.c_str());
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
	case eSwitchBool:
		//Text Size (char)
		unsigned short textSize = this->text.size();
		data->push_back(textSize & 0xFF);

		//Text (string)
		std::copy(this->text.begin(), this->text.end(), std::back_inserter(*data));

		//Text Colour (int)(RGB)
		data->push_back(this->textColour.A);
		data->push_back(this->textColour.B);
		data->push_back(this->textColour.G);
		data->push_back(this->textColour.R);

		//Font Size (Signed Short)
		data->push_back(this->fontSize & 0xFF);
		data->push_back((this->fontSize >> 8) & 0xFF);

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
	case eSwitchBool:

		data += "Text = " + this->text + "\n";
		data += "Text Colour = " + Functions::ToHex(this->textColour.ReturnInt(),4) + "\n";
		data += "Font Size = " + Functions::ToString(this->fontSize) + "\n";
		break;
	}
	return data;
}

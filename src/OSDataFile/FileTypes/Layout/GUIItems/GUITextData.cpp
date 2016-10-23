/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUITextData.h"

OSData::GUITextData::GUITextData(std::pair<unsigned short,unsigned short> location,ePosition horizontalPosition,ePosition verticalPosition,std::string text,RGBA textColour,signed short fontSize)
			:OSData::GUIItemData(GUITextType,location,{0,0},horizontalPosition,verticalPosition){
			 this->text = text;
			 this->textColour = textColour;
			 this->fontSize = fontSize;
}

OSData::GUITextData::GUITextData(Functions::DataReader* reader):OSData::GUIItemData(GUITextType,reader){
	unsigned int textSize = reader->ReadShort();
	this->text = reader->ReadString(textSize);

	this->textColour = reader->ReadInt();

	this->fontSize = reader->ReadShort();

}

OSData::GUITextData::GUITextData(xmlNode* node):GUIItemData(GUITextType,node){
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

void OSData::GUITextData::CheckValues(std::string name, std::string value){
	if (name == "Text")
		this->text = value;
	else if (name == "TextColour")
		this->textColour = Functions::StringToHex(value);
	else if (name == "FontSize")
		this->fontSize = atoi(value.c_str());
}

bool OSData::GUITextData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	if (GUIItemData::ToSaveToData(data) == false) return false;

	//textSize (Char);
	data->push_back(this->text.size() & 0xFF);
	data->push_back((this->text.size() >> 8) & 0xFF);

	//text (String);
	std::copy(this->text.begin(), this->text.end(), std::back_inserter(*data));

	//textColour (Int);
	data->push_back(this->textColour.A);
	data->push_back(this->textColour.B);
	data->push_back(this->textColour.G);
	data->push_back(this->textColour.R);

	//fontSize (Short);
	data->push_back(this->fontSize & 0xFF);
	data->push_back((this->fontSize >> 8) & 0xFF);

	return true;
}

std::string OSData::GUITextData::ToString(){
	std::string data;
	data += "GUITEXT\n";
	data += GUIItemData::ToString();
	data += "Text = " + this->text + "\n";
	data += "Colour = " + Functions::ToHex(this->textColour.ReturnInt(),4) + "\n";
	data += "Size = " + Functions::ToString(this->fontSize) + "\n";
	return data;
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIBoxDirectoryData.h"

OSData::GUIBoxDirectoryData::GUIBoxDirectoryData(std::string folderLocation,unsigned short verticalSize,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,RGBA selectColour){
		this->folderLocation = folderLocation;
		this->verticalSize = verticalSize;
		this->textColour = textColour;
		this->fontSize = fontSize;
		this->textBuffer = textBuffer;
		this->selectColour = selectColour;
}


OSData::GUIBoxDirectoryData::GUIBoxDirectoryData(Functions::DataReader* reader){

	unsigned int textSize = reader->ReadChar();
	this->folderLocation = reader->ReadString(textSize);
	this->verticalSize = reader->ReadShort();
	this->textColour = reader->ReadInt();
	this->fontSize = reader->ReadSignedShort();
	this->textBuffer = reader->ReadSignedShort();
	this->selectColour = reader->ReadInt();
}

OSData::GUIBoxDirectoryData::GUIBoxDirectoryData(xmlNode* node){
	if(node != NULL){

		xmlAttr* xmlAttribute = node->properties;
		while(xmlAttribute){
			this->CheckValues(((char*)xmlAttribute->name),((char*)xmlAttribute->children->content));
			xmlAttribute = xmlAttribute->next;
		}

//		while(node){
//			this->CheckValues(((char*)node->name),((char*)node->content));
//			node = node->next;
//		}
	}
}

void OSData::GUIBoxDirectoryData::CheckValues(std::string name, std::string value){
	if (name == "FolderLocation")
		this->folderLocation = value;
	else if (name == "VerticalSize")
		this->verticalSize = atoi(value.c_str());
	else if (name == "TextColour")
		this->textColour = Functions::StringToHex(value);
	else if (name == "FontSize")
	this->fontSize = atoi(value.c_str());
	else if (name == "TextBuffer")
		this->textBuffer = atoi(value.c_str());
	else if (name == "SelectColour")
		this->selectColour = Functions::StringToHex(value);
}
bool OSData::GUIBoxDirectoryData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;

	//Text Size (Char)
	data->push_back(static_cast<char>(this->folderLocation.size()));

	//Text (string)
	std::copy(this->folderLocation.begin(), this->folderLocation.end(), std::back_inserter(*data));

	//Vertical Size (Short)
	data->push_back(this->verticalSize & 0xFF);
	data->push_back((this->verticalSize >> 8) & 0xFF);

	//Text Colour (int)(RGB)
	data->push_back(this->textColour.A);
	data->push_back(this->textColour.B);
	data->push_back(this->textColour.G);
	data->push_back(this->textColour.R);

	//Font Size (Signed Short)
	data->push_back(this->fontSize & 0xFF);
	data->push_back((this->fontSize >> 8) & 0xFF);

	//Text Buffer (Signed Short)
	data->push_back(this->textBuffer & 0xFF);
	data->push_back((this->textBuffer >> 8) & 0xFF);

	//Image Colour
	data->push_back(this->selectColour.A);
	data->push_back(this->selectColour.B);
	data->push_back(this->selectColour.G);
	data->push_back(this->selectColour.R);

	return true;
}

std::string OSData::GUIBoxDirectoryData::ToString(){
	std::string data;
	data += "GUIBOXDIRECTORYDATA\n";

	data += "Folder Location = " + this->folderLocation + "\n";
	data += "Vetical Size = " + Functions::ToString(this->verticalSize) + "\n";
	data += "Text Colour = " + Functions::ToHex(this->textColour.ReturnInt(),4) + "\n";
	data += "Font Size = " + Functions::ToString(this->fontSize) + "\n";
	data += "Text Buffer = " + Functions::ToString(this->textBuffer) + "\n";
	data += "Selected Colour = " + Functions::ToHex(this->selectColour.ReturnInt(),4) + "\n";

	return data;
}

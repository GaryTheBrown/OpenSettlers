/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIButtonData.h"

OSData::GUIButtonData::GUIButtonData(GUIItemData baseData,std::string text,RGBA textColour,unsigned short fontSize, ImageData image, ImageData pressed,ImageData hover,GUIButtonTypeData buttonType,ReturnData returnData,bool multiSelect)
	:GUIItemData(GUIButtonType,baseData),
	text(text),	textColour(textColour), fontSize(fontSize),
	image(image), hover(hover), pressed(pressed),buttonType(buttonType),
	returnData(returnData), multiSelect(multiSelect){
}

OSData::GUIButtonData::GUIButtonData(Functions::DataReader* reader):OSData::GUIItemData(GUIButtonType,reader){
	unsigned char textSize = reader->ReadChar();
	this->text = reader->ReadString(textSize);
	this->textColour = reader->ReadInt();
	this->fontSize = reader->ReadShort();

	this->image.ReadData(reader);
	this->hover.ReadData(reader);
	this->pressed.ReadData(reader);
	this->buttonType = GUIButtonTypeData(reader);
	this->returnData = ReturnData(reader);

	this->multiSelect = reader->ReadChar() & 1;

}
OSData::GUIButtonData::GUIButtonData(xmlNode* node):GUIItemData(GUIButtonType,node){

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

void OSData::GUIButtonData::CheckValues(std::string name, std::string value){
	if (name == "Text")
		this->text = value;
	else if (name == "TextColour")
		this->textColour = Functions::StringToHex(value);
	else if (name == "FontSize")
		this->fontSize = atoi(value.c_str());
	else if (name == "ImageLocation")
		this->image.Location(value);
	else if (name == "ButtonColour")
		this->image.Colour(Functions::StringToHex(value));
	else if (name == "HoverImageLocation")
		this->hover.Location(value);
	else if (name == "HoverButtonColour")
		this->hover.Colour(Functions::StringToHex(value));
	else if (name == "PressedImageLocation")
		this->pressed.Location(value);
	else if (name == "PressedButtonColour")
		this->pressed.Colour(Functions::StringToHex(value));
	else if (name == "ButtonType") //TODO FIX THIS FOR FUNCTIONS
			this->buttonType = GUIButtonTypeData(GUIButtonTypeData::eNone);//this->GetButtonType(value);
	else if (name == "MenuEvent")
		this->returnData.MenuEvent(GetMenuEvent(value));
	else if (name == "MenuEventNumber")
		this->returnData.Int(atoi(value.c_str()));
	else if (name == "MenuEventString")
		this->returnData.String(value);
	else if (name == "MultiSelect")
		this->multiSelect = value=="true"?true:false;
}
bool OSData::GUIButtonData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	if (GUIItemData::ToSaveToData(data) == false) return false;

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

	if (this->image.ToSaveToData(data) == false) return false;
	if (this->hover.ToSaveToData(data) == false) return false;
	if (this->pressed.ToSaveToData(data) == false) return false;

	//Button Type
	this->buttonType.ToSaveToData(data);
	//Return Data
	this->returnData.ToSaveToData(data);

	//MultiSelect (Bool(Char))
	data->push_back(static_cast<char>(this->multiSelect?1:0));

	return true;
}

bool OSData::GUIButtonData::ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations){
	if (images == NULL) return false;

	if(this->image.ImageToNumbers(images,imageLocations) == false) return false;
	if(this->hover.ImageToNumbers(images,imageLocations) == false) return false;
	if(this->pressed.ImageToNumbers(images,imageLocations) == false) return false;

	return true;
}

bool OSData::GUIButtonData::LinkNumbers(std::vector<Functions::RGBImage*>* images){
	if (images == NULL) return false;

	if(this->image.LinkNumber(images) == false) return false;
	if(this->hover.LinkNumber(images) == false) return false;
	if(this->pressed.LinkNumber(images) == false) return false;

	return true;
}
std::string OSData::GUIButtonData::ToString(){
	std::string data;
	data += "GUIBUTTON\n";
	data += GUIItemData::ToString();

	data += "Text = " + this->text + "\n";
	data += "Text Colour = " + Functions::ToHex(this->textColour.ReturnInt(),4) + "\n";
	data += "Font Size = " + Functions::ToString(this->fontSize) + "\n";

	data += "Image = " + this->image.ToString();
	data += "Hover = " + this->hover.ToString();
	data += "Pressed = " + this->pressed.ToString();

	data += this->buttonType.ButtonTypeString();
	data += this->returnData.ToString();
	data += "MultiSelect = " + (this->multiSelect?std::string("True"):std::string("False")) + "\n";

	return data;
}

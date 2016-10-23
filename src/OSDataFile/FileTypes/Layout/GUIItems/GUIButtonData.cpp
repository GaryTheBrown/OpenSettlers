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

OSData::GUIButtonData::GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition horizontalPosition,ePosition verticalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,std::string imageLocation,std::string pressedLocation,std::string hoverLocation,eMenuEvent menuEvent,bool multiSelect)
	:GUIItemData(GUIButtonType,location,size,horizontalPosition,verticalPosition){	this->text = text;
	this->textColour = textColour;
	this->fontSize = fontSize;
	this->textBuffer = textBuffer;
	if (imageLocation != ""){
		this->image.Location(imageLocation);
	}else{
		this->image.None();
	}
	if (pressedLocation != ""){
	this->pressed.Location(pressedLocation);
	} else {
		this->pressed.None();
	}
	if (hoverLocation != ""){
		this->hover.Location(hoverLocation);
	} else {
		this->hover.None();
	}
	this->menuEvent = menuEvent;
	this->multiSelect = multiSelect;
}

OSData::GUIButtonData::GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition horizontalPosition,ePosition verticalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,signed int imageNumber,signed int pressedNumber,signed int hoverNumber,eMenuEvent menuEvent,bool multiSelect)
	:GUIItemData(GUIButtonType,location,size,horizontalPosition,verticalPosition){
	this->text = text;
	this->textColour = textColour;
	this->fontSize = fontSize;
	this->textBuffer = textBuffer;
	if (imageNumber > -1){
		this->image.Number(imageNumber);
	} else {
		this->image.None();
	}
	if (pressedNumber > -1){
		this->pressed.Number(pressedNumber);
	} else {
		this->pressed.None();
	}
	if (hoverNumber > -1){
		this->hover.Number(hoverNumber);
	} else {
		this->hover.None();
	}
	this->menuEvent = menuEvent;
	this->multiSelect = multiSelect;
}

OSData::GUIButtonData::GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition horizontalPosition,ePosition verticalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,RGBA buttonColour,RGBA pressedButtonColour,RGBA hoverButtonColour,eMenuEvent menuEvent,bool multiSelect)
	:GUIItemData(GUIButtonType,location,size,horizontalPosition,verticalPosition){
	this->text = text;
	this->textColour = textColour;
	this->fontSize = fontSize;
	this->textBuffer = textBuffer;
	this->image.Colour(buttonColour);
	this->pressed.Colour(pressedButtonColour);
	this->hover.Colour(hoverButtonColour);
	this->menuEvent = menuEvent;
	this->multiSelect = multiSelect;
}

OSData::GUIButtonData::GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition horizontalPosition,ePosition verticalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,Functions::RGBImage* button,Functions::RGBImage* pressedButton,Functions::RGBImage* hoverButton,eMenuEvent menuEvent,bool multiSelect)
:GUIItemData(GUIButtonType,location,size,horizontalPosition,verticalPosition){
	this->text = text;
	this->textColour = textColour;
	this->fontSize = fontSize;
	this->textBuffer = textBuffer;
	if (button != NULL){
		this->image.Data(button);
	} else {
		this->image.None();
	}
	if (pressedButton != NULL){
		this->pressed.Data(pressedButton);
	} else {
		this->pressed.None();
	}
	if (hoverButton != NULL){
		this->hover.Data(hoverButton);
	} else {
		this->hover.None();
	}
	this->menuEvent = menuEvent;
	this->multiSelect = multiSelect;
}


OSData::GUIButtonData::GUIButtonData(Functions::DataReader* reader):OSData::GUIItemData(GUIButtonType,reader){
	unsigned short textSize = reader->ReadShort();
	this->text = reader->ReadString(textSize);
	this->textColour = reader->ReadInt();
	this->fontSize = reader->ReadSignedShort();
	this->textBuffer = reader->ReadSignedShort();

	this->image.ReadData(reader);
	this->hover.ReadData(reader);
	this->pressed.ReadData(reader);

	this->menuEvent = static_cast<eMenuEvent>(reader->ReadChar());

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
	else if (name == "TextBuffer")
		this->textBuffer = atoi(value.c_str());
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
	else if (name == "MenuEvent")
		this->menuEvent = GetMenuEvent(value);
	else if (name == "MultiSelect")
		this->multiSelect = value=="true"?true:false;
}
bool OSData::GUIButtonData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	if (GUIItemData::ToSaveToData(data) == false) return false;

	//Text Size (Char)
	unsigned short textSize = this->text.size();
	data->push_back(textSize & 0xFF);
	data->push_back((textSize >> 8) & 0xFF);

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


	//Text Buffer (Signed Short)
	data->push_back(this->textBuffer & 0xFF);
	data->push_back((this->textBuffer >> 8) & 0xFF);

	if (this->image.ToSaveToData(data) == false) return false;
	if (this->hover.ToSaveToData(data) == false) return false;
	if (this->pressed.ToSaveToData(data) == false) return false;

	//Menu Event (Char)(eMenuEvent)
	data->push_back(static_cast<char>(this->menuEvent));
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
	data += "Text Buffer = " + Functions::ToString(this->textBuffer) + "\n";

	data += "Image = " + this->image.ToString();
	data += "Hover = " + this->hover.ToString();
	data += "Pressed = " + this->pressed.ToString();

	data += "Event = " + MenuEventToString(this->menuEvent) + "\n";
	data += "MultiSelect = " + (this->multiSelect?std::string("True"):std::string("False")) + "\n";

	return data;
}

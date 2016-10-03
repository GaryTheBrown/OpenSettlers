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

OSData::GUIButtonData::GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,unsigned int imageNumber,unsigned int pressedNumber,unsigned int hoverNumber,eMenuEvent menuEvent,bool multiSelect)
	:GUIItemData(GUIButtonType,location,size,verticalPosition,horizontalPosition){	this->text = text;
	this->textColour = textColour;
	this->fontSize = fontSize;
	this->textBuffer = textBuffer;
	this->imageNumber = imageNumber;
	this->pressedImageNumber = pressedNumber;
	this->hoverImageNumber = hoverNumber;
	this->menuEvent = menuEvent;
	this->multiSelect = multiSelect;
}

OSData::GUIButtonData::GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,RGBA buttonColour,RGBA pressedButtonColour,RGBA hoverButtonColour,eMenuEvent menuEvent,bool multiSelect)
	:GUIItemData(GUIButtonType,location,size,verticalPosition,horizontalPosition){
	this->text = text;
	this->textColour = textColour;
	this->fontSize = fontSize;
	this->textBuffer = textBuffer;
	this->buttonColour = buttonColour;
	this->pressedButtonColour = pressedButtonColour;
	this->hoverButtonColour = hoverButtonColour;
	this->menuEvent = menuEvent;
	this->multiSelect = multiSelect;
}

OSData::GUIButtonData::GUIButtonData(Functions::DataReader* reader)
:OSData::GUIItemData(GUIButtonType,reader){

	unsigned int textSize = reader->ReadChar();
	this->text = reader->ReadString(textSize,-1);
	this->textColour = reader->ReadInt();
	this->fontSize = reader->ReadSignedShort();
	this->textBuffer = reader->ReadSignedShort();

	unsigned int count = reader->ReadInt();
	if (count == 1)
		this->imageNumber = reader->ReadInt();
	else if (count == 2)
		this->buttonColour = reader->ReadInt();
	else
		this->imageLocation = reader->ReadString(count,-1);

	count = reader->ReadInt();
	if (count == 1)
		this->hoverImageNumber = reader->ReadInt();
	else if (count == 2)
		this->hoverButtonColour = reader->ReadInt();
	else
		this->hoverImageLocation = reader->ReadString(count,-1);

	count = reader->ReadInt();
	if (count == 1)
		this->pressedImageNumber = reader->ReadInt();
	else if (count == 2)
		this->pressedButtonColour = reader->ReadInt();
	else
		this->pressedImageLocation = reader->ReadString(count,-1);

	this->menuEvent = static_cast<eMenuEvent>(reader->ReadChar());

	this->multiSelect = reader->ReadChar() & 1;

}
OSData::GUIButtonData::GUIButtonData(std::string line)
						:GUIItemData(GUIButtonType,line),
						 menuEvent(MMNothing),
						 multiSelect(false){

	std::vector<std::pair<std::string,std::string>>* loadDataList = Functions::LoadFromTextLine(line);

	for(unsigned int i = 0; i < loadDataList->size();i++){

		if (loadDataList->at(i).first == "Text")
			this->text = loadDataList->at(i).second;
		if (loadDataList->at(i).first == "TextColour"){
			//Special
			std::string line = loadDataList->at(i).second;
			int pos = line.find_first_of('-');
			this->textColour.R = (unsigned char)atoi(line.substr(0, pos).c_str());
			std::string line2 = line.substr(pos+1);
			pos = line2.find_first_of('-');
			this->textColour.G = (unsigned char)atoi(line2.substr(0, pos).c_str());
			this->textColour.B = (unsigned char)atoi(line2.substr(pos+1).c_str());
		}
		if (loadDataList->at(i).first == "FontSize")
			this->fontSize = atoi(loadDataList->at(i).second.c_str());
		if (loadDataList->at(i).first == "TextBuffer")
			this->textBuffer = atoi(loadDataList->at(i).second.c_str());
		if (loadDataList->at(i).first == "ImageLocation")
			this->imageLocation = loadDataList->at(i).second;
		if (loadDataList->at(i).first == "HoverImageLocation")
			this->hoverImageLocation = loadDataList->at(i).second;
		if (loadDataList->at(i).first == "PressedImageLocation")
			this->pressedImageLocation = loadDataList->at(i).second;
		if (loadDataList->at(i).first == "ButtonColour"){
			//Special
			std::string line = loadDataList->at(i).second;
			int pos = line.find_first_of('-');
			this->buttonColour.R = (unsigned char)atoi(line.substr(0, pos).c_str());
			std::string line2 = line.substr(pos+1);
			pos = line2.find_first_of('-');
			this->buttonColour.G = (unsigned char)atoi(line2.substr(0, pos).c_str());
			std::string line3 = line.substr(pos+1);
			pos = line3.find_first_of('-');
			this->buttonColour.B = (unsigned char)atoi(line3.substr(0, pos).c_str());
			this->buttonColour.A = (unsigned char)atoi(line3.substr(pos+1).c_str());
		}
		if (loadDataList->at(i).first == "HoverButtonColour"){
			//Special
			std::string line = loadDataList->at(i).second;
			int pos = line.find_first_of('-');
			this->hoverButtonColour.R = (unsigned char)atoi(line.substr(0, pos).c_str());
			std::string line2 = line.substr(pos+1);
			pos = line2.find_first_of('-');
			this->hoverButtonColour.G = (unsigned char)atoi(line2.substr(0, pos).c_str());
			std::string line3 = line.substr(pos+1);
			pos = line3.find_first_of('-');
			this->hoverButtonColour.B = (unsigned char)atoi(line3.substr(0, pos).c_str());
			this->hoverButtonColour.A = (unsigned char)atoi(line3.substr(pos+1).c_str());
		}
		if (loadDataList->at(i).first == "PressedButtonColour"){
			//Special
			std::string line = loadDataList->at(i).second;
			int pos = line.find_first_of('-');
			this->pressedButtonColour.R = (unsigned char)atoi(line.substr(0, pos).c_str());
			std::string line2 = line.substr(pos+1);
			pos = line2.find_first_of('-');
			this->pressedButtonColour.G = (unsigned char)atoi(line2.substr(0, pos).c_str());
			std::string line3 = line.substr(pos+1);
			pos = line3.find_first_of('-');
			this->pressedButtonColour.B = (unsigned char)atoi(line3.substr(0, pos).c_str());
			this->pressedButtonColour.A = (unsigned char)atoi(line3.substr(pos+1).c_str());
		}
		if (loadDataList->at(i).first == "MenuEvent")
			this->menuEvent = (eMenuEvent)atoi(loadDataList->at(i).second.c_str());
		if (loadDataList->at(i).first == "MultiSelect")
			this->multiSelect = loadDataList->at(i).second=="true"?true:false;
	}

	delete loadDataList;
}

bool OSData::GUIButtonData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	if (GUIItemData::ToSaveToData(data) == false) return false;

	//Text Size (Char)
	data->push_back(static_cast<char>(this->text.size()));

	//Text (string)
	std::copy(this->text.begin(), this->text.end()-1, std::back_inserter(*data));

	//Text Colour (int)(RGB)
	data->push_back(this->textColour.R);
	data->push_back(this->textColour.G);
	data->push_back(this->textColour.B);
	data->push_back(this->textColour.A);

	//Font Size (Signed Short)
	data->push_back((this->fontSize >> 8) & 0xFF);
	data->push_back(this->fontSize & 0xFF);

	//Text Buffer (Signed Short)
	data->push_back((this->textBuffer >> 8) & 0xFF);
	data->push_back(this->textBuffer & 0xFF);

	unsigned short stringSize = this->imageLocation.size();
	if (stringSize > 0){
		//count (Short)
		data->push_back((stringSize >> 8) & 0xFF);
		data->push_back(stringSize & 0xFF);

		//string
		std::copy(this->imageLocation.begin(), this->imageLocation.end()-1, std::back_inserter(*data));
	}else{
		//count (Short)
		data->push_back(0);
		data->push_back(0);

		//ImageNumber (Short)
		data->push_back((this->imageNumber >> 8) & 0xFF);
		data->push_back(this->imageNumber & 0xFF);
	}

	stringSize = this->hoverImageLocation.size();
	if (stringSize > 0){
		//count (Short)
		data->push_back((stringSize >> 8) & 0xFF);
		data->push_back(stringSize & 0xFF);

		//string
		std::copy(this->hoverImageLocation.begin(), this->hoverImageLocation.end()-1, std::back_inserter(*data));
	}else{
		//count (Short)
		data->push_back(0);
		data->push_back(0);

		//ImageNumber (Short)
		data->push_back((this->hoverImageNumber >> 8) & 0xFF);
		data->push_back(this->hoverImageNumber & 0xFF);
	}

	stringSize = this->pressedImageLocation.size();
	if (stringSize > 0){
		//count (Short)
		data->push_back((stringSize >> 8) & 0xFF);
		data->push_back(stringSize & 0xFF);

		//string
		std::copy(this->pressedImageLocation.begin(), this->pressedImageLocation.end()-1, std::back_inserter(*data));
	}else{
		//count (Short)
		data->push_back(0);
		data->push_back(0);

		//ImageNumber (Short)
		data->push_back((this->pressedImageNumber >> 8) & 0xFF);
		data->push_back(this->pressedImageNumber & 0xFF);
	}

	//Menu Event (Char)(eMenuEvent)
	data->push_back(static_cast<char>(this->menuEvent));
	//MultiSelect (Bool(Char))
	data->push_back(static_cast<char>(this->multiSelect?1:0));

	return true;
}

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

OSData::GUITextData::GUITextData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition,std::string text,RGBA textColour,signed short fontSize)
			:OSData::GUIItemData(GUITextType,location,{0,0},verticalPosition,horizontalPosition),
			 text(text),
			 textColour(textColour),
			 fontSize(fontSize){
}

OSData::GUITextData::GUITextData(Functions::DataReader* reader)
			:OSData::GUIItemData(GUITextType,reader){
	unsigned int textSize = reader->ReadShort();
	this->text = reader->ReadString(textSize,-1);

	this->textColour = reader->ReadInt();

	this->fontSize = reader->ReadShort();

}
OSData::GUITextData::GUITextData(std::string line)
					:GUIItemData(GUITextType,line),
					text(""){

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
	}

	delete loadDataList;
}

OSData::GUITextData::~GUITextData() {}

bool OSData::GUITextData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	if (GUIItemData::ToSaveToData(data) == false) return false;

	//textSize (Char);
	data->push_back(this->text.size() & 0xFF);

	//text (String);
	std::copy(this->text.begin(), this->text.end()-1, std::back_inserter(*data));

	//textColour (Int);
	data->push_back(this->textColour.R);
	data->push_back(this->textColour.G);
	data->push_back(this->textColour.B);
	data->push_back(this->textColour.A);

	//fontSize (Short);
	data->push_back((this->fontSize >> 8) & 0xFF);
	data->push_back(this->fontSize & 0xFF);

	return true;
}

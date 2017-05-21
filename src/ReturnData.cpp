/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "ReturnData.h"

ReturnData::ReturnData(eMenuEvent rMenuEvent) {
	this->rMenuEvent = rMenuEvent;
}

ReturnData::ReturnData(eMenuEvent rMenuEvent, std::string rString) {
	this->rMenuEvent = rMenuEvent;
	this->rString = rString;
}

ReturnData::ReturnData(eMenuEvent rMenuEvent,unsigned int returnInt){
	this->rMenuEvent = rMenuEvent;
	this->rInt = returnInt;
}

ReturnData::ReturnData(eMenuEvent rMenuEvent,unsigned int returnInt , std::string rString){
	this->rMenuEvent = rMenuEvent;
	this->rInt = returnInt;
	this->rString = rString;
}

ReturnData::ReturnData(Functions::DataReader* reader){
	this->rMenuEvent = static_cast<eMenuEvent>(reader->ReadChar());

	eReturnExtra type = MenuEventReturnType(this->rMenuEvent);

	if (type & RDInt){
		this->rInt = reader->ReadInt();
	}
	if (type & RDString){
		unsigned char textSize = reader->ReadChar();
		this->rString = reader->ReadString(textSize);
	}
}

bool ReturnData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;

	//Menu Event (Char)(eMenuEvent)
	data->push_back(static_cast<char>(this->rMenuEvent));

	eReturnExtra type = MenuEventReturnType(this->rMenuEvent);

	if (type & RDInt){
		data->push_back(this->rInt & 0xFF);
		data->push_back((this->rInt >> 8) & 0xFF);
		data->push_back((this->rInt >> 16) & 0xFF);
		data->push_back((this->rInt >> 24) & 0xFF);
	}

	if (type & RDString){
		//Text Size (Char)
		unsigned char textSize = this->rString.size();
		data->push_back(textSize & 0xFF);

		//Text (string)
		std::copy(this->rString.begin(), this->rString.end(), std::back_inserter(*data));
	}

	return true;
}

std::string ReturnData::ToString(){
	std::string data;
	data += "Event = " + MenuEventToString(this->rMenuEvent);

	eReturnExtra type = MenuEventReturnType(this->rMenuEvent);

	if (type & RDInt){
	data += " :Int Value = " + Functions::ToString(this->rInt);
	}
	if (type & RDString){
		data += " :String Value = " + this->rString;
	}

	data += "\n";
	return data;
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "ImageData.h"


void OSData::ImageData::ReadData(Functions::DataReader* reader){
	unsigned short count = reader->ReadShort();
	if (count > 2)
		this->type = tLocation;
	else
		this->type = static_cast<ImageLocationType>(count);

	switch(this->type){
	case tLocation:
		this->location = reader->ReadString(count);
		break;
	case tNumber:
		this->number = reader->ReadInt();
		break;
	case tColour:
		this->colour = reader->ReadInt();
		break;
	case tNone:
	default:
		break;
	}
}
bool OSData::ImageData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;

	switch(this->type){
	case tNone:{
		//count (Short)
		data->push_back(0);
		data->push_back(0);
		break;
	}
	case tNumber:{
		//count (Short)
		data->push_back(1);
		data->push_back(0);

		//ImageNumber (int)
		data->push_back(this->number & 0xFF);
		data->push_back((this->number >> 8) & 0xFF);
		data->push_back((this->number >> 16) & 0xFF);
		data->push_back((this->number >> 24) & 0xFF);
		break;
	}
	case tColour:{
		//count (Short)
		data->push_back(2);
		data->push_back(0);

		//Image Colour
		data->push_back(this->colour.A);
		data->push_back(this->colour.B);
		data->push_back(this->colour.G);
		data->push_back(this->colour.R);
		break;
	}
	case tLocation:{
		unsigned short stringSize = this->location.size();
		//count (Short)
		data->push_back(stringSize & 0xFF);
		data->push_back((stringSize >> 8) & 0xFF);

		//string
		std::copy(this->location.begin(), this->location.end(), std::back_inserter(*data));
		break;
	}
	case tData:
		LOGSYSTEM->Error("Data Not Linked To a Number");
		return false;
	}
	return true;
}
bool OSData::ImageData::ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations){
	if (images == NULL) return false;

	if (this->type == tLocation){
		if (imageLocations == NULL){
			return false;
		}
		//First Check the Image is not already Loaded
		auto imageLocation = std::find(imageLocations->begin(), imageLocations->end(), this->location);
		if (imageLocation == imageLocations->end()){
			//Image not already loaded
			Functions::FileImage* imageFile = new Functions::FileImage();
			unsigned short* width = new unsigned short(0);
			unsigned short* height = new unsigned short(0);
			RGBA* rgbaData = imageFile->LoadImageToRGBA(this->location,width,height);
			this->image = new Functions::RGBImage(rgbaData,*width,*height);
			images->push_back(this->image);
			imageLocations->push_back(this->location);
			this->Number(images->size() - 1);
		} else {
			//Found Image in DB already
			auto index = std::distance(imageLocations->begin(), imageLocation);
			this->Number(index);
		}
	} else if (this->type == tData){
		//First Check the Image is not already Loaded
		auto image = std::find(images->begin(), images->end(), this->image);
		if (image == images->end()){
			//Image not already loaded
			images->push_back(this->image);
			this->Number(images->size() - 1);
		} else {
			//Found Image in DB already
			auto index = std::distance(images->begin(), image);
			this->Number(index);
		}
	}
	return true;
}

bool OSData::ImageData::LinkNumber(std::vector<Functions::RGBImage*>* images){
	if((this->image != NULL)||(images == NULL)) return false;
	if(this->type != tNumber) return true;

	this->image = (*images)[this->number];
	if (this->image == NULL) return false;
	return true;
}

std::string OSData::ImageData::ToString(){
	std::string data;
	switch(this->type){
	case tLocation:
		data += "Location = " + this->location + "\n";
		break;
	case tNumber:
		data += "Location Number = " + Functions::ToString(this->number) + "\n";
		break;
	case tColour:
		data += "Button Colour = " + Functions::ToHex(this->colour.ReturnInt(),4) + "\n";
		break;
	case tData:
		data += "Internal Image Data\n";
		break;
	case tNone:
	default:
		data += "BLANK\n";
		break;
	}

	return data;
}

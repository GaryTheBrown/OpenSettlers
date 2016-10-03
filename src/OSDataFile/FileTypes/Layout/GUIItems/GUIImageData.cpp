/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIImageData.h"

OSData::GUIImageData::GUIImageData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition,std::string imageLocation)
	:OSData::GUIItemData(GUIImageType,location,size,verticalPosition,horizontalPosition),
	imageLocation(imageLocation){
}

OSData::GUIImageData::GUIImageData(Functions::DataReader* reader)
	:OSData::GUIItemData(GUIImageType,reader){
	unsigned short count = reader->ReadShort();
	if (count == 0)
		this->imageNumber = reader->ReadShort();
	else
		this->imageLocation = reader->ReadString(count,-1);
}

OSData::GUIImageData::GUIImageData(std::string line)
	:GUIItemData(GUIImageType,line){

	std::vector<std::pair<std::string,std::string>>* loadDataList = Functions::LoadFromTextLine(line);

	for(unsigned int i = 0; i < loadDataList->size();i++){
		if (loadDataList->at(i).first == "ImageLocation")
			this->imageLocation = loadDataList->at(i).second;
	}
	delete loadDataList;
}

bool OSData::GUIImageData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	if (GUIItemData::ToSaveToData(data) == false) return false;

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

	return true;
}

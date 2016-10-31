/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIImageData.h"

OSData::GUIImageData::GUIImageData(GUIItemData baseData,ImageData image)
	:OSData::GUIItemData(GUIImageType,baseData),
	image(image){

}

OSData::GUIImageData::GUIImageData(Functions::DataReader* reader)
	:OSData::GUIItemData(GUIImageType,reader){
	this->image.ReadData(reader);
}

OSData::GUIImageData::GUIImageData(xmlNode* node):GUIItemData(GUIImageType,node){
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

void OSData::GUIImageData::CheckValues(std::string name, std::string value){
 	if (name == "ImageLocation")
		this->image.Location(value);
}

bool OSData::GUIImageData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	if (GUIItemData::ToSaveToData(data) == false) return false;
	if (this->image.ToSaveToData(data) == false) return false;

	return true;
}

bool OSData::GUIImageData::ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations){
	if (images == NULL) return false;
	return this->image.ImageToNumbers(images,imageLocations);
}

bool OSData::GUIImageData::LinkNumbers(std::vector<Functions::RGBImage*>* images){
	if (images == NULL) return false;
	return this->image.LinkNumber(images);
}

std::string OSData::GUIImageData::ToString(){
	std::string data;
	data += "GUIIMAGE\n";
	data += GUIItemData::ToString();
	data += this->image.ToString();
	return data;
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GFXImage.h"

GFXInterface::GFXImage::GFXImage(SystemInterface::System* system, OSData::GUIImageData* imageData)
			:GFXItem(system,OSData::GUIItemData::GUIImageType,(OSData::GUIItemData*)imageData){
	this->imageData = imageData;
	this->location = this->imageData->Location();
	this->size = this->imageData->Size();

	switch(this->imageData->Image().Type()){
	case OSData::ImageData::tLocation:
		this->image = this->system->LoadTexture(this->imageData->Image().Location());
		break;
	case OSData::ImageData::tNumber:
		this->image = this->system->LoadTexture(this->imageData->Image().Image());
		break;
	default:
		break;
	}
	if(this->size.first == 0) this->size.first = this->image->GetTextureSize().first;
	if(this->size.second == 0) this->size.second = this->image->GetTextureSize().second;
	this->CalculateLocation();
}

void GFXInterface::GFXImage::Draw(){

	std::pair<int,int> windowSize = this->system->display->GetWindowSize();
	std::pair<int,int> location = this->location;
	std::pair<int,int> size = this->image->GetTextureSize();

	if((this->imageData->Horizontal() == OSData::GUIItemData::FullTile)&&(this->imageData->Vertical() == OSData::GUIItemData::FullTile)){
		for(location.second = 0; location.second < windowSize.second; location.second += size.second){
			for(location.first = 0; location.first < windowSize.first; location.first += size.first){
				this->image->TextureToScreen(location);
			}
		}
	}else if (this->imageData->Horizontal() == OSData::GUIItemData::FullTile){
		for(location.first = 0; location.first < windowSize.first;location.first += size.first){
			this->image->TextureToScreen(location);
		}

	}else if (this->imageData->Vertical() == OSData::GUIItemData::FullTile){
		for(location.second = 0; location.second < windowSize.second;location.second += size.second){
			this->image->TextureToScreen(location);
		}
	}else
	this->image->TextureToScreen(this->location,this->size);
}

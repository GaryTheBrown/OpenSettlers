/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GFXItem.h"

GFXInterface::GFXItem::GFXItem(SystemInterface::System* system, OSData::GUIItemData::eGUIItemType itemType, OSData::GUIItemData* itemData) {
	this->itemType = itemType;
	this->itemData = itemData;
	this->system = system;
	this->image = NULL;
}

GFXInterface::GFXItem::~GFXItem() {
	if(this->image != NULL)
		this->image->~ImageContainer();
}
//SHARED FUNCTIONS
bool GFXInterface::GFXItem::IsMouseOver(){
	std::pair<int,int> mouseLocation = this->system->events->GetMouseLocation();

		if ((mouseLocation.first > this->location.first) && (mouseLocation.first < (this->location.first + this->size.first))&&
			(mouseLocation.second > this->location.second) && (mouseLocation.second < (this->location.second + this->size.second)))
			return true;
		else return false;
}
//VIRTUALS

void GFXInterface::GFXItem::CalculateLocation(std::pair<int,int> location,std::pair<int,int> windowSize){
	if (windowSize.first == 0 && windowSize.second == 0){
		windowSize = this->system->display->GetWindowSize();
	}
	if (this->image != NULL){
		std::pair<int,int> imageSize = this->image->GetTextureSize();

	    if(this->size.first == 0) this->size.first = imageSize.first;
		if(this->size.second == 0) this->size.second = imageSize.second;
	}
	switch(this->itemData->Horizontal()){
	case OSData::GUIItemData::FullTile:
	default:
		this->location.first = location.first;
		break;
	case OSData::GUIItemData::pNone:
	case OSData::GUIItemData::AlignLeft:
		this->location.first = location.first + this->itemData->Location().first;
		break;
	case OSData::GUIItemData::AlignRight:
		this->location.first = location.first + windowSize.first - this->size.first - this->itemData->Location().first;
		break;
	case OSData::GUIItemData::AlignCentre:
		this->location.first = location.first + windowSize.first/2 - this->size.first/2;
		break;
	case OSData::GUIItemData::FullStretch:
		this->size.first = windowSize.first - (this->location.first * 2);
		this->location.first += location.first;
		break;
	case OSData::GUIItemData::StretchSetSize://stretches from x from top/left for x size
		this->size.first = this->itemData->Size().first;
		this->location.first += location.first;
		break;
//TODO???
	case OSData::GUIItemData::StretchFromFrom://stretches from x from top/left to x from bottom/right
		this->size.first = windowSize.first - this->itemData->Size().first;
		this->location.first += location.first;
		break;
	case OSData::GUIItemData::StretchPercent://stretches for a percent of the screen size
		this->size.first = windowSize.first/100*this->itemData->Size().first;
		this->location.first += location.first;
		break;
	}

	switch(this->itemData->Vertical()){
	case OSData::GUIItemData::FullTile:
	default:
		this->location.second = location.second;
		break;
	case OSData::GUIItemData::pNone:
	case OSData::GUIItemData::AlignTop:
		this->location.second = location.second + this->itemData->Location().second;
		break;
	case OSData::GUIItemData::AlignBottom:
		this->location.second = location.second + windowSize.second - this->size.second - this->itemData->Location().second;
		break;
	case OSData::GUIItemData::AlignCentre:
		this->location.second = location.second + windowSize.second/2 - this->size.second/2;
		break;
	case OSData::GUIItemData::FullStretch:
		this->size.second = windowSize.second - (this->location.second * 2);
		this->location.second += location.second;
		break;
	case OSData::GUIItemData::StretchSetSize://stretches from x from top/left for x size
		this->size.second = this->itemData->Size().second;
		this->location.second += location.second;
		break;
	case OSData::GUIItemData::StretchFromFrom://stretches from x from top/left to x from bottom/right
		this->size.second = windowSize.second - this->itemData->Size().second;
		this->location.second += location.second;
		break;
	case OSData::GUIItemData::StretchPercent://stretches for a percent of the screen size
		this->size.second = windowSize.second/100*this->itemData->Size().second;
		this->location.second += location.second;
		break;
	}
}

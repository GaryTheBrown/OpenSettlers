/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GFXBox.h"

GFXInterface::GFXBox::GFXBox(SystemInterface::System* system,OSData::GUIBoxData* boxData)
	:GFXItem(system,OSData::GUIItemData::GUIBoxType,(OSData::GUIItemData*)boxData){
	this->boxData = boxData;
	this->image = this->system->CreateTexture(boxData->Size(),boxData->BackgroundColour());
	this->location = this->boxData->Location();
	this->size = this->boxData->Size();
	this->boxType = this->boxData->BoxType();
	this->multiSelect = this->boxData->MultiSelect();
	this->selected = NULL;

	if(this->boxData->ItemData() != NULL){
		this->itemList  = new std::vector<GFXItem*>();
		GFXItem* newItem;
		for(auto item=this->boxData->ItemData()->begin() ; item < this->boxData->ItemData()->end(); item++ ){
			switch ((*item)->ItemType()){
			default:
				break;
			case OSData::GUIItemData::GUIButtonType:
				newItem = new GFXButton(this->system,(OSData::GUIButtonData*)(*item));
				this->itemList->push_back(newItem);
				break;
			case OSData::GUIItemData::GUIImageType:
				newItem = new GFXImage(this->system,(OSData::GUIImageData*)(*item));
				this->itemList->push_back(newItem);
				break;
			case OSData::GUIItemData::GUISpacerType:
				newItem = new GFXSpacer(this->system,(OSData::GUISpacerData*)(*item));
				this->itemList->push_back(newItem);
				break;
			}
		}

	}else{
		LOGSYSTEM->Error("No Item data to Link into GFXBox");
	}

    //HERE CHECK FOR LIST TYPE AND SETUP
	this->CalculateLocation();

}
//TODO Finish this off. list view (should be easy set each item to new line
void GFXInterface::GFXBox::CalculateItems(){
	if(this->itemList != NULL){
	   	int locationH = 0;
		int largestHeight = 0;
		int locationW = 0;
	 	std::pair<unsigned short,unsigned short> itemSize;
	 	std::pair<unsigned short,unsigned short> itemLocation;
	   	switch(this->boxType){
	   	case OSData::GUIBoxData::tEmpty:
	   		break;
	   	case OSData::GUIBoxData::tGridView:
   			for(auto item=this->itemList->begin() ; item < this->itemList->end(); item++ ){
	   			itemSize = (*item)->GetSize();
	   			if(this->size.first < (locationW + itemSize.first)){
	   				locationH += largestHeight;
	   				locationW = 0;
	   			}
	   			if (this->size.second < (locationH + itemSize.second))
	   				break;
	   			itemLocation.first = this->location.first + locationW;
	   			itemLocation.second = this->location.second + locationH;
	   			(*item)->SetLocation(itemLocation);
	   			locationW += itemSize.first;
	   			if(itemSize.second > largestHeight) largestHeight = itemSize.second;
	   		}
	   		break;
	   	case OSData::GUIBoxData::tListView:
	   	case OSData::GUIBoxData::tListFullDir:
	   	case OSData::GUIBoxData::tListFolderDir:
	   	case OSData::GUIBoxData::tListFileDir:
	   		for(auto item=this->itemList->begin() ; item < this->itemList->end(); item++ ){
	   			itemLocation = this->location;
	   			itemLocation.second += locationH;
	   			itemSize = (*item)->GetSize();
	   			itemSize.first = this->size.first;
	   			(*item)->SetLocation(itemLocation);
	   			(*item)->SetSize(itemSize);
	   			locationH += itemSize.second;
	   		}
	   		break;
	   	case OSData::GUIBoxData::tFreeView:
	   		for(auto item=this->itemList->begin() ; item < this->itemList->end(); item++ ){
	   			(*item)->CalculateLocation(this->location,this->size);
	   		}
	   		break;
	   	}
	}
}

GFXInterface::GFXBox::~GFXBox() {
	if (this->itemList != NULL) {
		for(auto item=this->itemList->begin() ; item < this->itemList->end(); item++ ){
			delete (*item);
		}
		this->itemList->clear();
		delete this->itemList;
	}
}

void GFXInterface::GFXBox::Draw(){
	this->image->TextureToScreen(this->location,this->size);
    if(this->itemList != NULL){
    	for(auto item=this->itemList->begin() ; item < this->itemList->end(); item++ ){
    		(*item)->Draw();
    	}
    }

}
void GFXInterface::GFXBox::CalculateLocation(std::pair<int,int> location,std::pair<int,int> windowSize){
	GFXItem::CalculateLocation(location,windowSize);
	this->CalculateItems();
}

eMenuEvent GFXInterface::GFXBox::EventHandler(){
	if(this->IsMouseOver()){
		eMenuEvent returnEvent = MMNothing;
		if(this->itemList != NULL){
			for(auto item=this->itemList->end() -1 ; item > this->itemList->begin() -1; item-- ){
				returnEvent = (*item)->EventHandler();
    			if (returnEvent != MMNothing) return returnEvent;
    			if((*item)->Selected()){
    				if ((this->system->events->GetEvent() == SystemInterface::eMouseButtonDown)&&(this->GetMultiSelect() == false)){
    					//check if any are selected if so unselect them
    					if(this->selected != NULL) this->selected->Unselect();

    					if (this->selected != (*item)){
    						if((*item)->Selected())
    							this->selected = (GFXButton*)(*item);
    					}
    					else this->selected = NULL;
    				}
    			}
			}
		}
	}
	return MMNothing;
}

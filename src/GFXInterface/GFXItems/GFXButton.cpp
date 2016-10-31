/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GFXButton.h"

GFXInterface::GFXButton::GFXButton(SystemInterface::System* system, OSData::GUIButtonData* buttonData)
				:GFXItem(system,OSData::GUIItemData::GUIButtonType,(OSData::GUIItemData*)buttonData){
	this->buttonData = buttonData;
	this->location = this->buttonData->Location();
	this->size = this->buttonData->Size();
	this->text = this->buttonData->Text();

	switch(this->buttonData->Image().Type()){
	case OSData::ImageData::tLocation:
		this->image = this->system->LoadTexture(this->buttonData->Image().Location());
		break;
	case OSData::ImageData::tColour:
		this->image = this->system->CreateTexture(this->buttonData->Size(),this->buttonData->Image().Colour());
		break;
	case OSData::ImageData::tNumber:
		this->image = this->system->LoadTexture(this->buttonData->Image().Image());
		break;
	default:
		break;
	}
	switch(this->buttonData->Hover().Type()){
		case OSData::ImageData::tLocation:
			this->hover = this->system->LoadTexture(this->buttonData->Hover().Location());
			break;
		case OSData::ImageData::tColour:
			this->hover = this->system->CreateTexture(this->buttonData->Size(),this->buttonData->Hover().Colour());
			break;
		case OSData::ImageData::tNumber:
			this->hover = this->system->LoadTexture(this->buttonData->Hover().Image());
			break;
		default:
			break;
	}
	switch(this->buttonData->Pressed().Type()){
		case OSData::ImageData::tLocation:
			this->pressed = this->system->LoadTexture(this->buttonData->Pressed().Location());
			break;
		case OSData::ImageData::tColour:
			this->pressed = this->system->CreateTexture(this->buttonData->Size(),this->buttonData->Pressed().Colour());
			break;
		case OSData::ImageData::tNumber:
			this->pressed = this->system->LoadTexture(this->buttonData->Pressed().Image());
			break;
		default:
			break;
	}
	if(this->text != ""){
		this->textImage = this->system->TextToImage(this->text,this->buttonData->TextColour(), this->buttonData->FontSize());
		this->textSize = this->textImage->GetTextureSize();
		if (this->size.second < this->textSize.second)
			this->size.second = this->textSize.second + 2;
		if (this->size.first < this->textSize.first)
			this->size.first = this->textSize.first + 2;

		this->textLocation.first = (this->location.first + this->size.first/2 - this->textSize.first/2);
		this->textLocation.second = (this->location.second + this->size.second/2 - this->textSize.second/2);
	}
	else
		this->textImage = NULL;

	this->uniqueImage = true;
	this->selectable = this->buttonData->MultiSelect();
	this->call = this->buttonData->MenuEvent();

	this->selected = false;
	this->clicked = false;

	this->CalculateLocation();
}

GFXInterface::GFXButton::~GFXButton() {
	if(this->uniqueImage){
		if (this->hover != NULL)this->hover->~ImageContainer();
		if (this->pressed != NULL)this->pressed->~ImageContainer();
	}
	if (this->textImage != NULL)this->textImage->~ImageContainer();
}
void GFXInterface::GFXButton::TextCorrection(){
	if (this->buttonData->FontSize() == 0){
		//button size - buffer size*2
	}else {

	}
}

void GFXInterface::GFXButton::SetLocation(std::pair<int,int> location){
	this->location = location;

	if(this->textImage != NULL){
		this->textLocation.first = (this->location.first + this->size.first/2 - this->textSize.first/2);
		this->textLocation.second = (this->location.second + this->size.second/2 - this->textSize.second/2);
	}
}

void GFXInterface::GFXButton::SetSize(std::pair<int,int> size){
	if (size.first > 0) this->size.first = size.first;
	if (size.second > 0) this->size.second = size.second;

	if(this->textImage != NULL){
		this->textLocation.first = (this->location.first + this->size.first/2 - this->textSize.first/2);
		this->textLocation.second = (this->location.second + this->size.second/2 - this->textSize.second/2);
	}
}

void GFXInterface::GFXButton::Draw(){

	SystemInterface::ImageContainer* buttonToDraw = this->image;

	if((this->clicked)&&(this->IsMouseOver())&&(this->pressed != NULL))
		buttonToDraw = this->pressed;
	else if((this->selected)&&(this->pressed != NULL))
		buttonToDraw = this->pressed;
	else if((this->IsMouseOver())&&(this->hover != NULL))
		buttonToDraw = this->hover;

	buttonToDraw->TextureToScreen(this->location, this->size);


	if (this->textImage != NULL)
		this->textImage->TextureToScreen(this->textLocation, this->textSize);

}

void GFXInterface::GFXButton::Pressed(){
	if(this->IsMouseOver()){
		if(this->selectable)
			this->selected = !this->selected;
		else
			this->clicked = true;
	}
}

void GFXInterface::GFXButton::Unselect(){
	this->selected = false;
}

bool GFXInterface::GFXButton::Released(){
	if(this->IsMouseOver()){
		if (this->clicked){
			this->clicked = false;
			return true;
		}
	}
	this->clicked = false;
	return false;
}

void GFXInterface::GFXButton::CalculateLocation(std::pair<int,int> location,std::pair<int,int> windowSize){
	GFXItem::CalculateLocation(location,windowSize);
	if(this->textImage != NULL){
		this->textSize = this->textImage->GetTextureSize();
		this->textLocation.first = (this->location.first + this->size.first/2 - this->textSize.first/2);
		this->textLocation.second = (this->location.second + this->size.second/2 - this->textSize.second/2);
	}
}

eMenuEvent GFXInterface::GFXButton::EventHandler(){

		// If a button on the mouse is pressed.
		if (this->system->events->GetEvent() == SystemInterface::eMouseButtonDown){
			// If the left button was pressed.
			if (this->system->events->GetMouseButton() == SystemInterface::MouseButtonLeft){
				//is Mouse Over Button
				if(this->IsMouseOver()){
        	   		this->Pressed();
        	   		return MMNothing;
	   		}
   	    }
	}
	else if (this->system->events->GetEvent() == SystemInterface::eMouseButtonUp){
		// If the left button was pressed.
	   	if (this->system->events->GetMouseButton() == SystemInterface::MouseButtonLeft){
	   		if(this->Released())
	   	    	return this->Call();
	   	}
	}
		return MMNothing;
}

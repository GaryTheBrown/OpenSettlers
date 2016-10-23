/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GFXText.h"

GFXInterface::GFXText::GFXText(SystemInterface::System* system, std::string text, RGBA textColour, std::pair<int,int> location)
		:GFXItem(system,OSData::GUIItemData::GUITextType,(OSData::GUIItemData*)textData){

	this->textData = NULL;
	this->image = this->system->TextToImage(text,textColour);
	this->size = this->image->GetTextureSize();
	this->location = location;

}

GFXInterface::GFXText::GFXText(SystemInterface::System* system, OSData::GUITextData* textData)
		:GFXItem(system,OSData::GUIItemData::GUITextType,(OSData::GUIItemData*)textData){

	this->textData = textData;
	this->image = this->system->TextToImage(this->textData->Text(),this->textData->TextColour());
	this->location = this->textData->GetLocation();
	this->size = this->image->GetTextureSize();
	this->CalculateLocation();
}

void GFXInterface::GFXText::Draw(){
	if(this->image != NULL)
			this->image->TextureToScreen(this->location);
}

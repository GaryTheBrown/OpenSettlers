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

GFXInterface::GFXText::GFXText(SystemInterface::System* system, ConfigList* configList, std::string text, RGBA textColour, unsigned short fontSize, std::pair<int,int> location, OSData::GameAddons addons)
		:GFXItem(system,configList,OSData::GUIItemData::GUITextType,(OSData::GUIItemData*)textData,addons){

	this->textData = NULL;
	this->image = this->system->TextToImage(text,textColour,fontSize);
	this->size = this->image->GetTextureSize();
	this->location = location;

}

GFXInterface::GFXText::GFXText(SystemInterface::System* system, ConfigList* configList, OSData::GUITextData* textData, OSData::GameAddons addons)
		:GFXItem(system,configList,OSData::GUIItemData::GUITextType,(OSData::GUIItemData*)textData,addons){

	this->textData = textData;
	this->image = this->system->TextToImage(this->textData->Text(),this->textData->TextColour(),this->textData->FontSize());
	this->location = this->textData->Location();
	this->size = this->image->GetTextureSize();
	this->CalculateLocation();
}

void GFXInterface::GFXText::Draw(){
	if(this->image != NULL){
		if (this->visible&&this->enabled)
			this->image->TextureToScreen(this->location);
	}
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "SDL2Fonts.h"

SystemInterface::SDL2Fonts::SDL2Fonts() {
	TTF_Init();
	this->masterFont.fontName = "arial.ttf";
	this->masterFont.fontLocation = "";
}

SystemInterface::SDL2Fonts::~SDL2Fonts() {

	for(auto item = this->masterFont.fontSizes.begin(); item != this->masterFont.fontSizes.end(); item++) {
		TTF_CloseFont(item->second);
	}

	TTF_Quit();
}

TTF_Font* SystemInterface::SDL2Fonts::MasterFont(unsigned short fontSize){

	auto it = this->masterFont.fontSizes.find(fontSize);

	if (it != this->masterFont.fontSizes.end())
		return it->second;
	else{
		TTF_Font* mFont = TTF_OpenFont(this->masterFont.fontName.c_str(), fontSize);
		this->masterFont.fontSizes.insert(std::pair<int, TTF_Font*>(fontSize, mFont));
		return mFont;
	}
}

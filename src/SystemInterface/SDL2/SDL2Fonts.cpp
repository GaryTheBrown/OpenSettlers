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
	this->masterFont = TTF_OpenFont( "arial.ttf", 22 );
}

SystemInterface::SDL2Fonts::~SDL2Fonts() {
    TTF_CloseFont(this->masterFont);
	TTF_Quit();
}

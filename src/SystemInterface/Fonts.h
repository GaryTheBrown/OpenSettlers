/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once

#include <string>
//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//TODO FINISH OFF FONT SYSTEM
//further improve the fonts to load all in system
// and allow any in Game/Data/Fonts/  or /Data/Fonts/
namespace SystemInterface {
	class Fonts {
	protected:

	public:
		TTF_Font* masterFont;

		Fonts(){this->masterFont = NULL;};
		virtual ~Fonts(){};
	};
}

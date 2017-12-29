/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef SYSTEMINTERFACE_FONTS_H
#define SYSTEMINTERFACE_FONTS_H

#include <string>
#include <map>
#include <SDL2/SDL_ttf.h>

//TODO FINISH OFF FONT SYSTEM
//further improve the fonts to load all in system
//	/usr/share/fonts
//	/usr/local/share/fonts
// and allow any in Game/Data/Fonts/  or /Data/Fonts/
//http://www.cplusplus.com/forum/windows/148218/

namespace SystemInterface {
	class Fonts {
	protected:
		struct Font{
			std::string fontLocation;
			std::string fontName;
			std::map<int, TTF_Font*> fontSizes;
		} masterFont;

	public:
		virtual ~Fonts(){

		}
		virtual TTF_Font* MasterFont(unsigned short fontSize) = 0;
	};
}

#endif
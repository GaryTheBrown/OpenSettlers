/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef SYSTEMINTERFACE_SDL2_SDL2FONTS_H
#define SYSTEMINTERFACE_SDL2_SDL2FONTS_H

#include <SDL2/SDL_ttf.h>
#include "../Fonts.h"

namespace SystemInterface {
	class SDL2Fonts : public Fonts {
	public:
		SDL2Fonts();
		virtual ~SDL2Fonts();
		TTF_Font* MasterFont(unsigned short fontSize);
	};
}

#endif
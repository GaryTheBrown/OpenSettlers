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
#include <utility>
//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>


#include "../System.h"
#include "SDL2Display.h"
#include "SDL2ImageContainer.h"
#include "SDL2Events.h"
#include "SDL2Fonts.h"

class SDL2Display;

namespace SystemInterface {
	class SDL2System : public System {
	private:

	public:
		//Only visible inside SDL2 System
		SDL2Display* sdl2Display;

		//Constructor
		SDL2System(std::string windowName,bool fullscreen);
		virtual ~SDL2System();

		//Image functions
		virtual ImageContainer* LoadTexture(std::string path);
		virtual ImageContainer* CreateTexture(std::pair<int,int> size, RGBA colour);
		virtual ImageContainer* TextToImage(std::string text, RGBA colour);
		virtual void TextureToScreen(ImageContainer* imageContainer);

	};
}

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

#include <SDL2/SDL_image.h>

#include <string>
#include <utility>
#include "../System.h"
#include "../ImageContainer.h"

#include "SDL2System.h"
class SDL2System;

namespace SystemInterface {
	class SDL2ImageContainer: public ImageContainer {
	private:
		SDL2System* system;
		SDL_Texture* texture;
		SDL_Rect sdlRect;

	public:

		SDL2ImageContainer(SDL2System* system);
		SDL2ImageContainer(SDL2System* system, SDL2ImageContainer* imageContainer);
		virtual ~SDL2ImageContainer();

		virtual bool LoadTexture(std::string path);
		virtual bool CreateTexture(std::pair<int,int> size, RGBA colour);
		virtual bool TextToImage(std::string text, RGBA colour);

		virtual void TextureToScreen();
		virtual void TextureToScreen(std::pair<int,int> location);
		virtual void TextureToScreen(std::pair<int,int> location,std::pair<int,int> size);

		//Getters
		virtual std::pair<int,int> GetTextureSize();
	};
}

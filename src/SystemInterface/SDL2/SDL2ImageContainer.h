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
#include "../../Functions/Image/RGBImage.h"
#include "../System.h"
#include "../ImageContainer.h"

#include "SDL2System.h"

namespace SystemInterface {
	class SDL2System;
	class SDL2ImageContainer: public ImageContainer {
	private:
		SDL2System* system;
		SDL_Texture* texture;
		SDL_Rect sdlRect;

	public:

		SDL2ImageContainer(SDL2System* system);
		SDL2ImageContainer(SDL2System* system, SDL2ImageContainer* imageContainer);
		virtual ~SDL2ImageContainer();

		bool LoadTexture(std::string path);
		bool LoadTexture(Functions::RGBImage* memoryImage);
		bool CreateTexture(std::pair<int,int> size, RGBA colour);
		bool TextToImage(std::string text, RGBA colour);

		void TextureToScreen();
		void TextureToScreen(std::pair<int,int> location);
		void TextureToScreen(std::pair<int,int> location,std::pair<int,int> size);

		//Getters
		virtual std::pair<int,int> GetTextureSize();

	private:
		bool SurfaceToTexture(SDL_Surface* surface);
	};
}

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
#include "../../Log.h"

#include "../System.h"
#include "../ImageContainer.h"

#include "OGL21System.h"
class OGL21System;

namespace SystemInterface {
	class OGL21ImageContainer: public ImageContainer {
	private:

		OGL21System* system;
		GLuint textureID = 0;
		std::pair<int,int> size = {0,0};
		std::pair<int,int> location = {0,0};

	public:
		OGL21ImageContainer(OGL21System* system);
		OGL21ImageContainer(OGL21System* system, OGL21ImageContainer* imageContainer);
		virtual ~OGL21ImageContainer();


		virtual bool LoadTexture(std::string path);
		virtual bool CreateTexture(std::pair<int,int> size, RGBA colour);
		virtual bool TextToImage(std::string text, RGBA colour);

		virtual void TextureToScreen();
		virtual void TextureToScreen(std::pair<int,int> location);
		virtual void TextureToScreen(std::pair<int,int> location,std::pair<int,int> size);

		//Getters
		virtual std::pair<int,int> GetTextureSize();


	private:
		bool textureToGPU(SDL_Surface* surface);
	};
}

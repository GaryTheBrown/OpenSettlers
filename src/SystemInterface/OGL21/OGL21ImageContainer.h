/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef SYSTEMINTERFACE_OGL21_OGL21IMAGECONTAINER_H
#define SYSTEMINTERFACE_OGL21_OGL21IMAGECONTAINER_H

#include <SDL2/SDL_image.h>

#include <string>
#include <utility>
#include "../../Functions/Image/RGBImage.h"
#include "../System.h"
#include "../ImageContainer.h"

#include "OGL21System.h"


namespace SystemInterface {
	class OGL21System;
	class OGL21ImageContainer: public ImageContainer {
	private:

		OGL21System* system;
		GLuint textureID = 0;
		std::pair<int,int> size = {0,0};
		std::pair<int,int> location = {0,0};

	public:
		explicit OGL21ImageContainer(OGL21System* system);
		OGL21ImageContainer(OGL21System* system, OGL21ImageContainer* imageContainer);
		virtual ~OGL21ImageContainer();


		bool LoadTexture(std::string path);
		bool LoadTexture(Functions::RGBImage* image);
		bool CreateTexture(std::pair<int,int> size, RGBA colour);
		bool TextToImage(std::string text, RGBA colour, unsigned short fontSize);

		void TextureToScreen();
		void TextureToScreen(std::pair<int,int> location);
		void TextureToScreen(std::pair<int,int> location,std::pair<int,int> size);

		//Getters
		std::pair<int,int> GetTextureSize();


	private:
		bool TextureToGPU(SDL_Surface* surface);
	};
}

#endif
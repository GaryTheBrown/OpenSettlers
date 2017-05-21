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

//OpenGL
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include "../../Functions/Image/RGBImage.h"
#include "../System.h"
#include "../SDL2/SDL2Events.h"
#include "../SDL2/SDL2Fonts.h"
#include "OGL21Display.h"
#include "OGL21ImageContainer.h"

namespace SystemInterface {

	class OGL21Display;
	class OGL21System : public System {
	private:

	public:
		//Only visible inside SDL2 System
		OGL21Display* oGL21Display;

		//Constructor
		OGL21System(std::string windowName,std::pair<int,int> windowSize,bool fullscreen);
		virtual ~OGL21System();

		//Image functions
		ImageContainer* LoadTexture(std::string path);
		ImageContainer* LoadTexture(Functions::RGBImage* memoryImage);
		ImageContainer* CreateTexture(std::pair<int,int> size, RGBA colour);
		ImageContainer* TextToImage(std::string text, RGBA colour, unsigned short fontSize);
		void TextureToScreen(ImageContainer* imageContainer);

	};
}

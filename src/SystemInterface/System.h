/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef SYSTEMINTERFACE_SYSTEM_H
#define SYSTEMINTERFACE_SYSTEM_H

#include <string>
#include <utility>
#include "../Functions/Image/RGBA.h"
#include "../Functions/Image/RGBImage.h"
#include "../Functions/Timer.h"
#include "ImageContainer.h"
#include "Events.h"
#include "Display.h"
#include "Fonts.h"
class Display;
namespace SystemInterface {
	class System {
	private:
	protected:
		ConfigList* configList;
		std::string gameLocation = "";
	public:
		Events* events = NULL;
		Display* display = NULL;
		Fonts* fonts = NULL;

		virtual ~System(){};

		//Functions
		void SetGameLocation(std::string gameLocation){this->gameLocation = gameLocation;}

		//FPS Functions

		//Texture Functions
		virtual ImageContainer* LoadTexture(std::string path) = 0;
		virtual ImageContainer* LoadTexture(Functions::RGBImage* memoryImage) = 0;
		virtual ImageContainer* CreateTexture(std::pair<int,int> size, RGBA colour) = 0;
		virtual ImageContainer* TextToImage(std::string text, RGBA colour, unsigned short fontSize) = 0;
		virtual void TextureToScreen(ImageContainer* imageContainer) = 0;

	};
}

#endif
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
#include "../Functions/Image/RGBA.h"
#include "../Functions/Image/RGBImage.h"

namespace SystemInterface {
	class ImageContainer {
	protected:

	public:

		virtual ~ImageContainer(){};

		virtual bool LoadTexture(std::string path) = 0;
		virtual bool LoadTexture(Functions::RGBImage* memoryImage) = 0;
		virtual bool CreateTexture(std::pair<int,int> size, RGBA colour) = 0;
		virtual bool TextToImage(std::string text, RGBA colour) = 0;

		//Texture Draw Functions
		virtual void TextureToScreen() = 0;
		virtual void TextureToScreen(std::pair<int,int> location) = 0;
		virtual void TextureToScreen(std::pair<int,int> location,std::pair<int,int> size) = 0;

		virtual std::pair<int,int> GetTextureSize() = 0;

	};
}

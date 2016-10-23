/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "OGL21System.h"

SystemInterface::OGL21System::OGL21System(std::string windowName, std::pair<int,int> windowSize, bool fullscreen) {
	// Start SDL2
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	this->events = new SDL2Events();
	this->fonts = new SDL2Fonts();

	this->oGL21Display = new OGL21Display(this, windowSize, fullscreen);
	this->display = this->oGL21Display;
	this->display->SetWindowName(windowName);
}

SystemInterface::OGL21System::~OGL21System() {
	this->display->~Display();
	SDL_QuitSubSystem(SDL_INIT_VIDEO|SDL_INIT_TIMER);

	this->fonts->~Fonts();
	this->events->~Events();
	SDL_Quit();
}

SystemInterface::ImageContainer* SystemInterface::OGL21System::LoadTexture(std::string path){
    //Container
	ImageContainer* imageContainer = new OGL21ImageContainer(this);
	if(this->gameLocation == "")
		imageContainer->LoadTexture(path);
	else
		imageContainer->LoadTexture((this->gameLocation + path));
    return imageContainer;
}

SystemInterface::ImageContainer* SystemInterface::OGL21System::LoadTexture(Functions::RGBImage* memoryImage){
    //Container
	ImageContainer* imageContainer = new OGL21ImageContainer(this);
	imageContainer->LoadTexture(memoryImage);
    return imageContainer;
}

void SystemInterface::OGL21System::TextureToScreen(ImageContainer* imageContainer){
	imageContainer->TextureToScreen();
}

SystemInterface::ImageContainer* SystemInterface::OGL21System::CreateTexture(std::pair<int,int> size, RGBA colour){
    //Container

	ImageContainer* imageContainer = new OGL21ImageContainer(this);
	imageContainer->CreateTexture(size,colour);
    return imageContainer;
}
SystemInterface::ImageContainer* SystemInterface::OGL21System::TextToImage(std::string text, RGBA colour){
    //Container
	ImageContainer* imageContainer = new OGL21ImageContainer(this);
	imageContainer->TextToImage(text,colour);
    return imageContainer;
}


/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "SDL2System.h"

SystemInterface::SDL2System::SDL2System(std::string windowName,std::pair<int,int> windowSize,bool fullscreen) {

	//Start SDL2
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	this->sdl2Display = new SDL2Display(this,windowSize,fullscreen);
	this->display = this->sdl2Display;
	this->display->SetWindowName(windowName);

	this->events = new SDL2Events();
	this->fonts = new SDL2Fonts();

}

SystemInterface::SDL2System::~SDL2System() {
	this->display->~Display();
	SDL_QuitSubSystem(SDL_INIT_VIDEO|SDL_INIT_TIMER);

	this->fonts->~Fonts();
	this->events->~Events();
	SDL_Quit();
}

SystemInterface::ImageContainer* SystemInterface::SDL2System::LoadTexture(std::string path){
    //Container
	ImageContainer* imageContainer = new SDL2ImageContainer(this);
	if(this->gameLocation == "")
		imageContainer->LoadTexture(path);
	else
		imageContainer->LoadTexture((this->gameLocation + path));
    return imageContainer;
}

SystemInterface::ImageContainer* SystemInterface::SDL2System::LoadTexture(Functions::RGBImage* memoryImage){
	ImageContainer* imageContainer = new SDL2ImageContainer(this);
	imageContainer->LoadTexture(memoryImage);
	return imageContainer;
}

void SystemInterface::SDL2System::TextureToScreen(ImageContainer* imageContainer){
	imageContainer->TextureToScreen();
}

SystemInterface::ImageContainer* SystemInterface::SDL2System::CreateTexture(std::pair<int,int> size, RGBA colour){
    //Container
	ImageContainer* imageContainer = new SDL2ImageContainer(this);
	imageContainer->CreateTexture(size,colour);
    return imageContainer;
}
SystemInterface::ImageContainer* SystemInterface::SDL2System::TextToImage(std::string text, RGBA colour, unsigned short fontSize){
    //Container
	ImageContainer* imageContainer = new SDL2ImageContainer(this);
	imageContainer->TextToImage(text,colour,fontSize);
    return imageContainer;
}

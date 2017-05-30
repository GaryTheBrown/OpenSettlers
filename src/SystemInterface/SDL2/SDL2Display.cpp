/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "SDL2Display.h"

SystemInterface::SDL2Display::SDL2Display(System* system,ConfigList* configList){
	this->system = system;
	this->configList = configList;
	this->windowName = "OpenSettlers";

	//Gets Monitor resolution
	SDL_GetCurrentDisplayMode(0,&this->currentDesktopMode);
	SDL_GetDesktopDisplayMode(0,&this->systemDesktopMode);

	auto windowSize =  configList->GetValue<std::pair<int,int> >("windowsize");
	bool fullscreen = configList->GetValue<bool>("fullscreen");

	//Checks for Inital Window Size (setting up from cli and eventually from config)
	if(windowSize.first < this->MINWINDOWSIZE.first) windowSize.first = this->MINWINDOWSIZE.first;
	if(windowSize.second < this->MINWINDOWSIZE.second) windowSize.second = this->MINWINDOWSIZE.second;

	//create screen checking if fullscreen needed.
	this->window = SDL_CreateWindow(this->windowName.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			windowSize.first, windowSize.second,
			SDL_WINDOW_RESIZABLE);

	if(fullscreen){
		SDL_SetWindowFullscreen(this->window,SDL_WINDOW_FULLSCREEN_DESKTOP);
	}

	this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED );

	IMG_Init(IMG_INIT_PNG);

	//Start FPS Timers
	this->FPS.Start(this->GetTick());
	this->update.Start(this->GetTick());
}

SystemInterface::SDL2Display::~SDL2Display() {
	//is this needed?
	if (&this->systemDesktopMode != &this->currentDesktopMode)
		SDL_SetWindowDisplayMode(this->window, &this->systemDesktopMode);

	SDL_DestroyWindow(window);
	IMG_Quit();
}

void SystemInterface::SDL2Display::SetWindowName(std::string name){
	if(name != "") this->windowName = name;
	SDL_SetWindowTitle(this->window,this->windowName.c_str());
}

void SystemInterface::SDL2Display::SetWindowSize(std::pair<int,int> size){
	//std::pair<int,int> size = this->configList->GetValue<std::pair<int,int> >("windowsize");
	if(size.second == 0) size.second = 1;
	if(size.first == 0) size.first = 1;
	SDL_SetWindowSize(this->window,size.first,size.second);
	//this->configList->SetValue<std::pair<int,int> >("windowsize",size);
	this->windowSize = size;
}

void SystemInterface::SDL2Display::SetWindowFullscreen(){
	bool fullscreen = this->configList->GetValue<bool>("fullscreen");
	if (fullscreen){
		SDL_SetWindowFullscreen(this->window,SDL_FALSE);
		//this->configList->SetValue<std::pair<int,int> >("windowsize",this->tmpFullscreenWindowSize);
		this->SetWindowSize(this->tmpFullscreenWindowSize);
		fullscreen = false;
	}
	else{
		this->tmpFullscreenWindowSize = this->windowSize;//this->configList->GetValue<std::pair<int,int> >("windowsize");
		SDL_SetWindowFullscreen(this->window,SDL_WINDOW_FULLSCREEN_DESKTOP);
		fullscreen = true;
	}
	this->configList->SetValue<bool>("fullscreen",fullscreen);
}

std::pair<int,int> SystemInterface::SDL2Display::GetScreenSize(){
	SDL_GetCurrentDisplayMode(0, &this->currentDesktopMode);
	std::pair<int,int> size;
	size.second = currentDesktopMode.h;
	size.first = currentDesktopMode.w;
	return size;
}


void SystemInterface::SDL2Display::ClearToColour(RGBA colour){
	SDL_SetRenderDrawColor(this->renderer, colour.R, colour.G, colour.B, 255);
    SDL_RenderClear(this->renderer);
}


void SystemInterface::SDL2Display::FlipScreen(){
	SDL_RenderPresent(this->renderer);
}

void SystemInterface::SDL2Display::FPSWait(){
    //If we want to cap the frame rate
    if(this->bLockFPS){
    	unsigned int ticks = this->tLockFPS.GetTicks(this->GetTick());
    	if (ticks < 1000/this->MAXFPS ){
    		//Sleep the remaining frame time
    		SDL_Delay(1000/this->MAXFPS - ticks);
    	}
    }
}

void SystemInterface::SDL2Display::FPSRestart(){
	this->tLockFPS.Start(this->GetTick());
}

double SystemInterface::SDL2Display::CalculateFPS(){
    this->frame++;
    unsigned int curentTick = this->GetTick();
	if( this->update.GetTicks(curentTick) >= 1000 ){
		this->update.Start(curentTick);
		return this->frame / (this->FPS.GetTicks(curentTick) / 1000.0);
	}
	return 0;
}

void SystemInterface::SDL2Display::ShowFPSCounter(){
	if(this->bShowFPS){
		float fps = this->CalculateFPS();
		if (fps != 0){
			std::string FPSWindowName = this->windowName + ":FPS=" + Functions::ToString(fps);
			SDL_SetWindowTitle(this->window,FPSWindowName.c_str());
		}
	}
}
unsigned int SystemInterface::SDL2Display::GetTick(){
	return SDL_GetTicks();
}

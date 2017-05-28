/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "OGL21Display.h"

SystemInterface::OGL21Display::OGL21Display(System* system,ConfigList* configList) {
	this->system = system;
	this->configList = configList;
	this->windowName = "OpenSettlers";

	//Gets Monitor resolution
	SDL_GetCurrentDisplayMode(0,&this->currentDesktopMode);
	SDL_GetDesktopDisplayMode(0,&this->systemDesktopMode);

	auto windowSize =  configList->GetValue<std::pair<int,int> >("windowsize");
	bool fullScreen = configList->GetValue<bool>("fullscreen");

	//Checks for Inital Window Size (setting up from cli and eventually from config)
 	if(windowSize.first < this->MINWINDOWSIZE.first) windowSize.first = this->MINWINDOWSIZE.first;
 	if(windowSize.second < this->MINWINDOWSIZE.second) windowSize.second = this->MINWINDOWSIZE.second;

	/*----------------------
	 * SDL_OpenGL Attributes
	 ----------------------*/
    //Use OpenGL 2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );


    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);

    //Set inital Window Size
    if(fullScreen){
    	this->tmpFullscreenWindowSize = windowSize;
    	windowSize.first = this->systemDesktopMode.w;
    	windowSize.second = this->systemDesktopMode.h;
    }

   	//create screen checking if fullscreen needed.
   	this->window = SDL_CreateWindow(this->windowName.c_str(),
   			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			windowSize.first, windowSize.second,
			SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

	if(fullScreen){
    	SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);
	}

	this->mainContext = SDL_GL_CreateContext(this->window);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0f, windowSize.first, windowSize.second, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	//Initialize clear colour and depth settings
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClearDepth(1.0f);

	//Enable texturing
	glEnable(GL_TEXTURE_2D);

    //Set blending
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLoadIdentity();

	IMG_Init(IMG_INIT_PNG);
}

SystemInterface::OGL21Display::~OGL21Display() {
	//is this needed?
	if (&this->systemDesktopMode != &this->currentDesktopMode)
		SDL_SetWindowDisplayMode(this->window, &this->systemDesktopMode);

	SDL_GL_DeleteContext(this->mainContext);
	SDL_DestroyWindow(this->window);
	IMG_Quit();
}

void SystemInterface::OGL21Display::SetWindowName(std::string name){
	if(name != "") this->windowName = name;
	SDL_SetWindowTitle(this->window,this->windowName.c_str());
}

void SystemInterface::OGL21Display::SetWindowSize(){
	std::pair<int,int> size = this->configList->GetValue<std::pair<int,int> >("windowSize");
	if (size.second == 0) size.second = 1;
	if (size.first == 0) size.first = 1;

	SDL_SetWindowSize(this->window,size.first,size.second);
	glViewport(0, 0, size.first, size.second);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, size.first, size.second, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	this->configList->SetValue<std::pair<int,int> >("windowSize",size);
}

void SystemInterface::OGL21Display::SetWindowFullscreen(){
	bool fullScreen = this->configList->GetValue<bool>("fullscreen");
	if (fullScreen){
		SDL_SetWindowFullscreen(this->window,SDL_FALSE);
		this->configList->SetValue<std::pair<int,int> >("windowSize",this->tmpFullscreenWindowSize);
		this->SetWindowSize();
		fullScreen = false;
	}
	else{
		this->tmpFullscreenWindowSize = this->configList->GetValue<std::pair<int,int> >("windowSize");

		this->configList->SetValue<std::pair<int,int> >("windowSize",{this->systemDesktopMode.w,this->systemDesktopMode.h});
		this->SetWindowSize();
		SDL_SetWindowFullscreen(this->window,SDL_WINDOW_FULLSCREEN);
		fullScreen = true;
	}
	this->configList->SetValue<bool>("fullscreen",fullScreen);
}

std::pair<int,int> SystemInterface::OGL21Display::GetScreenSize(){
	SDL_GetCurrentDisplayMode(0, &this->currentDesktopMode);
	std::pair<int,int> size;
	size.second = currentDesktopMode.h;
	size.first = currentDesktopMode.w;
	return size;
}


void SystemInterface::OGL21Display::ClearToColour(RGBA colour){
	float R,G,B;
	R = (1.0f/255)*colour.R;
	G = (1.0f/255)*colour.G;
	B = (1.0f/255)*colour.B;
	glClearColor(R, G, B, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}


void SystemInterface::OGL21Display::FlipScreen(){
	SDL_GL_SwapWindow(this->window);
}

void SystemInterface::OGL21Display::FPSWait(){
    //If we want to cap the frame rate
    if(this->bLockFPS){
    	unsigned int ticks = this->tLockFPS.GetTicks(this->GetTick());
    	if (ticks < 1000/this->MAXFPS){
    		//Sleep the remaining frame time
    		SDL_Delay(1000/this->MAXFPS - ticks);
    	}
    }
}

void SystemInterface::OGL21Display::FPSRestart(){
	this->tLockFPS.Start(this->GetTick());
}

double SystemInterface::OGL21Display::CalculateFPS(){
    this->frame++;
    unsigned int curentTick = this->GetTick();
	if( this->update.GetTicks(curentTick) >= 1000 ){
		this->update.Start(curentTick);
		return this->frame / (this->FPS.GetTicks(curentTick) / 1000.0);
	}
	return 0;
}

void SystemInterface::OGL21Display::ShowFPSCounter(){
	if(this->bShowFPS){
		float fps = this->CalculateFPS();
		if (fps != 0){
			std::string FPSWindowName = this->windowName + ":FPS=" + Functions::ToString(fps);
			SDL_SetWindowTitle(this->window,FPSWindowName.c_str());
		}
	}
}
unsigned int SystemInterface::OGL21Display::GetTick(){
	return SDL_GetTicks();
}

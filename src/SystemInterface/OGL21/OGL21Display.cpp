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

SystemInterface::OGL21Display::OGL21Display(System* system, bool fullscreen) {
	this->system = system;
	this->windowName = "OpenSettlers";
	this->fullScreen = fullscreen;

	//Gets Monitor resolution
	SDL_GetCurrentDisplayMode(0,&this->currentDesktopMode);
	SDL_GetDesktopDisplayMode(0,&this->systemDesktopMode);

	/*----------------------
	 * SDL_OpenGL Attributes
	 ----------------------*/
    //Use OpenGL 2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );


    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);


    //Set inital Window Size
    if(this->fullScreen){
    	this->currentWindowSize.first = this->systemDesktopMode.w;
    	this->currentWindowSize.second = this->systemDesktopMode.h;
    	this->windowSize = this->MINWINDOWSIZE;
    }else{
    	this->currentWindowSize = this->MINWINDOWSIZE;
    }
   	//create screen checking if fullscreen needed.
   	this->window = SDL_CreateWindow(this->windowName.c_str(),
   			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			this->currentWindowSize.first, this->currentWindowSize.second,
			SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

	if(this->fullScreen){
    	SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);
	}

	this->mainContext = SDL_GL_CreateContext(this->window);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0f, this->currentWindowSize.first, this->currentWindowSize.second, 0.0f, 0.0f, 1.0f);
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

std::pair<int,int> SystemInterface::OGL21Display::GetWindowSize(){
	return this->currentWindowSize;
}

void SystemInterface::OGL21Display::SetWindowSize(std::pair<int,int> size){
	if (size.second == 0) size.second = 1;
	if (size.first == 0) size.first = 1;

	SDL_SetWindowSize(this->window,size.first,size.second);

	glViewport(0, 0, size.first, size.second);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, size.first, size.second, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	this->currentWindowSize = size;
}

void SystemInterface::OGL21Display::SetWindowFullscreen(){
	if (this->fullScreen){
		SDL_SetWindowFullscreen(this->window,SDL_FALSE);
		this->SetWindowSize(this->windowSize);
		this->fullScreen = false;
	}
	else{
		this->windowSize = this->GetWindowSize();
		this->SetWindowSize({this->systemDesktopMode.h,this->systemDesktopMode.w});
		SDL_SetWindowFullscreen(this->window,SDL_WINDOW_FULLSCREEN);
		this->fullScreen = true;
	}
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

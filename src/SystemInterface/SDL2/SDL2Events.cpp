/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "SDL2Events.h"

SystemInterface::SDL2Events::SDL2Events() {
	SDL_InitSubSystem(SDL_INIT_EVENTS);
	this->event = SDL_Event();
}

SystemInterface::SDL2Events::~SDL2Events() {
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

bool SystemInterface::SDL2Events::GetNextEvent() {
	if (SDL_PollEvent(&this->event) !=0)
		return true;
	return false;
}

SystemInterface::eEvent SystemInterface::SDL2Events::GetEvent() {
	if (this->event.type == SDL_QUIT)
		return eQuit;
	if (this->event.type == SDL_WINDOWEVENT){
		switch (this->event.window.event) {
	    case SDL_WINDOWEVENT_RESIZED:
	    	this->windowResizeSize.first = this->event.window.data1;
	    	this->windowResizeSize.second = this->event.window.data2;
	    	return eWindowResized;
	    case SDL_WINDOWEVENT_MINIMIZED:
	    	return eWindowMinimized;
	    case SDL_WINDOWEVENT_MAXIMIZED:
	    	this->windowResizeSize.first = this->event.window.data1;
	    	this->windowResizeSize.second = this->event.window.data2;
	    	return eWindowMaximized;
	    case SDL_WINDOWEVENT_RESTORED:
	    	this->windowResizeSize.first = this->event.window.data1;
	    	this->windowResizeSize.second = this->event.window.data2;
	    	return eWindowRestored;
	    case SDL_WINDOWEVENT_SHOWN:
	    case SDL_WINDOWEVENT_HIDDEN:
	    case SDL_WINDOWEVENT_EXPOSED:
	    case SDL_WINDOWEVENT_MOVED:
	    case SDL_WINDOWEVENT_ENTER:
	    case SDL_WINDOWEVENT_LEAVE:
	    case SDL_WINDOWEVENT_FOCUS_GAINED:
	    case SDL_WINDOWEVENT_FOCUS_LOST:
	    case SDL_WINDOWEVENT_CLOSE:
	    default:
	    	return eWindow;
	    }
	}
	if (this->event.type == SDL_KEYDOWN)
		return eKeyboardDown;
	if (this->event.type == SDL_KEYUP)
		return eKeyboardUp;
	if (this->event.type == SDL_MOUSEBUTTONDOWN)
		return eMouseButtonDown;
	if (this->event.type == SDL_MOUSEBUTTONUP)
		return eMouseButtonUp;
	if (this->event.type == SDL_MOUSEMOTION)
		return eMouseMotion;
	if (this->event.type == SDL_MOUSEWHEEL)
		return eMouseWheel;

	return eNone;
}
SystemInterface::eKeyboardKey SystemInterface::SDL2Events::GetKey(){
	return (eKeyboardKey)((int)this->event.key.keysym.scancode);
}

SystemInterface::eKeyboardMod SystemInterface::SDL2Events::GetKeyMod(){
	return (eKeyboardMod)((int)this->event.key.keysym.mod);
}

SystemInterface::eMouseButton SystemInterface::SDL2Events::GetMouseButton(){
if (this->event.button.button == SDL_BUTTON_LEFT)
	return MouseButtonLeft;
if (this->event.button.button == SDL_BUTTON_MIDDLE)
	return MouseButtonMiddle;
if (this->event.button.button == SDL_BUTTON_RIGHT)
	return MouseButtonRight;
return MBNone;
}

std::pair<int,int> SystemInterface::SDL2Events::GetMouseLocation(){
	std::pair<int,int> location;
	SDL_GetMouseState(&location.first,&location.second);
	return location;
}

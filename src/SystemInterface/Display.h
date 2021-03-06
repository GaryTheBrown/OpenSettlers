/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef SYSTEMINTERFACE_DISPLAY_H
#define SYSTEMINTERFACE_DISPLAY_H

#include <SDL2/SDL.h>
#include <string>
#include <utility>
#include "../ConfigList.h"
#include "../Functions/Timer.h"
#include "../Functions/Image/RGBA.h"

#include "System.h"


namespace SystemInterface {
class System;
	class Display {
	protected:

		System* system = NULL;
		ConfigList* configList;

		//Constant System Settings.
		const std::pair<int,int> MINWINDOWSIZE = {800,600};

		//for use when exiting fullscreen to remember the size.
		std::pair<int,int> tmpFullscreenWindowSize;

		//Look at setting up an option to Max out FPS for your monitor
		unsigned int MAXFPS;
		bool bLockFPS;
		bool bShowFPS;
		unsigned int frame = 0;
		Functions::Timer tLockFPS, FPS, update;

		//Display Options
		std::string windowName;
		std::pair<int,int> windowSize = MINWINDOWSIZE;

	public:
		virtual ~Display(){};

		//Internal
		std::pair<int,int> GetWindowMINSize(){return this->MINWINDOWSIZE;}
		std::pair<int,int> GetWindowSize(){return this->windowSize;}
		std::string GetWindowName(){return this->windowName;}
		virtual void SetWindowName(std::string name = ""){this->windowName = name;};
		virtual void SetWindowFullscreen() = 0;

		//Virtual
		//Clear Window to Colour
		virtual void ClearToColour(RGBA colour) = 0;

		//flip screen
		virtual void FlipScreen() = 0;

		//Window size
		virtual void SetWindowSize(std::pair<int,int> size) = 0;

		//Screen Size
		virtual std::pair<int,int> GetScreenSize() = 0;

		void LockFPS(){this->bLockFPS = true;};
		void UnLockFPS(){this->bLockFPS = false;};
		void ShowFPS(){this->bShowFPS = true;};
		void HideFPS(){this->bShowFPS = false;};
		bool GetShowFPS(){return this->bShowFPS;};
		virtual void FPSWait() = 0;
		virtual void FPSRestart() = 0;
		virtual unsigned int GetTick() = 0;
		virtual double CalculateFPS() = 0;
		virtual	void ShowFPSCounter() = 0;
	};
}

#endif
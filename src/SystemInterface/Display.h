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

#include <SDL2/SDL.h>
#include <string>
#include <utility>
#include "../Functions/Timer.h"
#include "../Functions/Image/RGBA.h"

#include "System.h"


namespace SystemInterface {
class System;
	class Display {
	protected:

		System* system = NULL;

		//Constant System Settings.
		const std::pair<int,int> MINWINDOWSIZE = {600,800};
		std::pair<int,int> currentWindowSize;
		std::pair<int,int> windowSize; //for use when fullscreened and exited to remember the size.

		//Look at setting up an option to Max out FPS for your monitor
		const unsigned int MAXFPS = 30;
		bool bLockFPS = true;
		bool bShowFPS = false;
		unsigned int frame = 0;
		Functions::Timer tLockFPS, FPS, update;

		//Display Options
		std::string windowName;
		bool fullScreen = false;

	public:
		virtual ~Display(){};

		//Internal
		std::pair<int,int> GetWindowMINSize(){return this->MINWINDOWSIZE;}
		std::string GetWindowName(){return this->windowName;}
		virtual void SetWindowName(std::string name = ""){this->windowName = name;};
		virtual void SetWindowFullscreen() = 0;




		//Virtual
		//Clear Window to Colour
		virtual void ClearToColour(RGBA colour) = 0;

		//flip screen
		virtual void FlipScreen() = 0;

		//Window size
		virtual std::pair<int,int> GetWindowSize() = 0;
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

		std::pair<int,int> GetMinWindowSize(){return MINWINDOWSIZE;};
	};
}

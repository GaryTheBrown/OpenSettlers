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

#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Display.h"
#include "../../Functions/To.h"
#include "OGL21ImageContainer.h"
namespace SystemInterface {
	class OGL21Display : public Display {
	private:

			SDL_DisplayMode currentDesktopMode;
			SDL_DisplayMode systemDesktopMode;

			SDL_Window* window;
			SDL_GLContext mainContext;

	public:

		OGL21Display(System* system, bool fullscreen);
		virtual ~OGL21Display();

		//Window
		virtual void SetWindowName(std::string name = "");
		virtual std::pair<int,int> GetWindowSize();
		virtual void SetWindowSize(std::pair<int,int> size);
		virtual void SetWindowFullscreen();

		//Screen
		virtual std::pair<int,int> GetScreenSize();
		virtual void ClearToColour(RGBA colour = {0,0,0});
		virtual void FlipScreen();

		//FPS
		virtual void FPSWait();
		virtual void FPSRestart();
		virtual unsigned int GetTick();
		virtual double CalculateFPS();
		virtual void ShowFPSCounter();

	};
}

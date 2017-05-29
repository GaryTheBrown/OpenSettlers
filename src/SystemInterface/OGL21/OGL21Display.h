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
#include "../../ConfigList.h"
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

		OGL21Display(System* system,ConfigList* configList);
		virtual ~OGL21Display();

		//Window
		void SetWindowName(std::string name = "");
		void SetWindowSize(std::pair<int,int> size);
		void SetWindowFullscreen();

		//Screen
		std::pair<int,int> GetScreenSize();
		void ClearToColour(RGBA colour = {0,0,0});
		void FlipScreen();

		//FPS
		void FPSWait();
		void FPSRestart();
		unsigned int GetTick();
		double CalculateFPS();
		void ShowFPSCounter();

	};
}

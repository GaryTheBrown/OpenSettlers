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
#include "SDL2ImageContainer.h"
#include "../Display.h"
#include "../../Functions/To.h"

namespace SystemInterface {
	class SDL2Display : public Display {
	private:

			SDL_DisplayMode currentDesktopMode;
			SDL_DisplayMode systemDesktopMode;
			SDL_Window* window;
			SDL_Renderer* renderer;
	public:

		SDL2Display(System* system,ConfigList* configList);
		virtual ~SDL2Display();

		//Window
		void SetWindowName(std::string name = "");
		std::pair<int,int> GetWindowSize();
		void SetWindowSize();
		void SetWindowFullscreen();

		//Screen
		std::pair<int,int> GetScreenSize();
		void ClearToColour(RGBA colour);
		void FlipScreen();

		//FPS
		void FPSWait();
		void FPSRestart();
		unsigned int GetTick();
		double CalculateFPS();
		void ShowFPSCounter();

		//SDL FUNCTIONS to ensure renderer is kept private
		SDL_Texture* SDLCreateTextureFromSurface(SDL_Surface* loadedSurface){return SDL_CreateTextureFromSurface(this->renderer, loadedSurface );};
		SDL_Texture* SDLCreateTexture(std::pair<int,int> size){return SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.first, size.second);};
		void SDLSetRenderTarget(SDL_Texture* texture = NULL){SDL_SetRenderTarget(this->renderer, texture);};
		void SDLSetRenderDrawColor(RGBA colour){SDL_SetRenderDrawColor(this->renderer, colour.R, colour.G, colour.B, colour.A );};
		void SDLRenderClear(){SDL_RenderClear(this->renderer);};
		void SDLRenderCopy(SDL_Texture* texture, SDL_Rect* fromLocation,SDL_Rect* toLocation){SDL_RenderCopy(this->renderer, texture, fromLocation, toLocation);};
	};
}

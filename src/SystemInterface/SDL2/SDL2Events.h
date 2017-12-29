/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef SYSTEMINTERFACE_SDL2_SDL2EVENTS_H
#define SYSTEMINTERFACE_SDL2_SDL2EVENTS_H

#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>

#include "../Events.h"

namespace SystemInterface {
	class SDL2Events: public Events {
	private:
		SDL_Event event;

	public:
		SDL2Events();
		virtual ~SDL2Events();

		bool GetNextEvent();
		eEvent GetEvent();
		eKeyboardKey GetKey();
		eKeyboardMod GetKeyMod();
		eMouseButton GetMouseButton();
		std::pair<int,int> GetMouseLocation();

	};
}

#endif
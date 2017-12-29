/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef FUNCTIONS_TIMER_H
#define FUNCTIONS_TIMER_H

namespace Functions{
	class Timer {
	private:
		unsigned int startTicks = 0;
		unsigned int pausedTicks = 0;
		bool paused = false;
		bool started = false;

	public:
		Timer(){};
		virtual ~Timer(){};

		//The various clock actions
		void Start(unsigned int time);
		void Stop();
		void Pause(unsigned int time);
		void Unpause(unsigned int time);

		//Gets the timer's time
		unsigned int GetTicks(unsigned int time);
		bool GetStarted();
		bool GetPaused();

	};
}

#endif
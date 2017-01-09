/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Timer.h"

void Functions::Timer::Start(unsigned int time){
	this->started = true;
	this->paused = false;

	//Get the current clock time
	this->startTicks = time;
}

void Functions::Timer::Stop(){
	//Stop the timer
	this->started = false;

	//Unpause the timer
	this->paused = false;
}

void Functions::Timer::Pause(unsigned int time){
	//If the timer is running and isn't already paused
	if((this->started == true)&&(this->paused == false)){
		//Pause the timer
		this->paused = true;

		//Calculate the paused ticks
		this->pausedTicks = time - this->startTicks;
	}
}

void Functions::Timer::Unpause(unsigned int time){
	//If the timer is paused
	if(this->paused == true){
		//Unpause the timer
		this->paused = false;

		//Reset the starting ticks
		this->startTicks = time - this->pausedTicks;

		//Reset the paused ticks
		this->pausedTicks = 0;
	}
}

unsigned int Functions::Timer::GetTicks(unsigned int time){
	//If the timer is running
	if(this->started == true){
		//If the timer is paused
		if(this->paused == true){
			//Return the number of ticks when the timer was paused
			return this->pausedTicks;
		}else{
			//Return the current time minus the start time
			return time - this->startTicks;
		}
	}

	//If the timer isn't running
	return 0;
}

bool Functions::Timer::GetStarted(){
	return this->started;
}

bool Functions::Timer::GetPaused(){
	return paused;
}

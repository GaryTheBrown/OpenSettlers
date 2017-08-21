/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Game.h"

GameInterface::Game::Game(SystemInterface::System* system, ConfigList* configList, OSData::GameType* gameType, signed int startMenuNumberOverride) {
	this->system = system;
	this->configList = configList;
	this->gameType = gameType;

	unsigned int startMenuNumber = startMenuNumberOverride;
	if(startMenuNumberOverride == -1){
		startMenuNumber = this->gameType->StartMenuNumber();
	}
	this->menu = new GameMenu(this->system,this->configList,this->gameType->MenuLayouts(),startMenuNumber,this->gameType->AddonsIncluded());

}

GameInterface::Game::~Game() {
	if (this->menu != NULL) this->menu->~GameMenu();
}

ReturnData GameInterface::Game::Loop(){
	//MENU LOOP UNTIL EXIT
	bool quit = false;
	while (!quit){
		if (this->menu != NULL){
			ReturnData gfxReturn = this->menu->Loop();
			switch(gfxReturn.MenuEvent()){
			case MMQuit:
				return gfxReturn;
				break;
			default:
				break;
			}
		}
		else quit = true;
	}
	return ReturnData(MMNothing);
}

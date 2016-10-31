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

GameInterface::Game::Game(SystemInterface::System* system, OSData::GameType* gameType) {
	this->system = system;

	this->system->SetGameLocation("Games/TheSettlers3/");
	this->gameType = gameType;
	this->menu = new GameMenu(this->system,this->gameType->MenuLayouts(),this->gameType->StartMenuNumber());

}

GameInterface::Game::~Game() {
	if (this->menu != NULL) this->menu->~GameMenu();
}

GFXInterface::GFXReturn GameInterface::Game::Loop(){
	//MENU LOOP UNTIL EXIT
	bool quit = false;
	while (!quit){
		if (this->menu != NULL){
			GFXInterface::GFXReturn gfxReturn = this->menu->Loop();
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
	return GFXInterface::GFXReturn(MMNothing);
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GameMenu.h"

GameInterface::GameMenu::GameMenu(SystemInterface::System* system, std::vector<OSData::MenuLayout*>* menuLayouts, unsigned int startMenuNumber):
	system(system),
	menuLayouts(menuLayouts),
	startMenuNumber(startMenuNumber){

	for(auto layout = this->menuLayouts->begin() ; layout < this->menuLayouts->end(); layout++){
		if ((*layout)->MenuID() == this->startMenuNumber){
			this->menu = new GFXInterface::GFXMenu(system,(*layout));
			return;
		}
	}
	LOGSYSTEM->Error("Starting Menu ID Not Found");
}

GameInterface::GameMenu::~GameMenu(){
	if (this->menu != NULL)
		delete this->menu;
}

GFXInterface::GFXReturn GameInterface::GameMenu::Loop(){
	if (this->menu != NULL){
		//MENU LOOP
		while (true){
			GFXInterface::GFXReturn gfxReturn = this->menu->Loop();
			switch(gfxReturn.MenuEvent()){
			case MMQuit:
				return gfxReturn;
			default:
				break;
			}
		}
	}
	//if while loop where to ever fail return nothing or if the menu ID was not found.
	return GFXInterface::GFXReturn(MMNothing);
}

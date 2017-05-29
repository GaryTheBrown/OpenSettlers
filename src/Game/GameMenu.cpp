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

GameInterface::GameMenu::GameMenu(SystemInterface::System* system, ConfigList* configList, std::vector<OSData::MenuLayout*>* menuLayouts, unsigned int startMenuNumber, OSData::GameAddons addons):
	system(system),
	configList(configList),
	menuLayouts(menuLayouts),
	startMenuNumber(startMenuNumber),
	addons(addons){


	for (unsigned int startNumber = this->startMenuNumber; startNumber >= 0; startNumber--){
		for(auto layout = this->menuLayouts->begin() ; layout < this->menuLayouts->end(); layout++){
			if ((*layout)->MenuID() == startNumber){
				this->menu = new GFXInterface::GFXMenu(system,this->configList,(*layout),this->addons);
				return;
			}
		}
	}
	LOGSYSTEM->Error("Starting Menu ID Not Found");
}

GameInterface::GameMenu::~GameMenu(){
	if (this->menu != NULL)
		delete this->menu;
}

ReturnData GameInterface::GameMenu::Loop(){
	if (this->menu != NULL){
		//MENU LOOP
		while (true){
			ReturnData gfxReturn = this->menu->Loop();
			switch(gfxReturn.MenuEvent()){
			case MMQuit:
				return gfxReturn;
			case GMGotoMenu:{
				bool found = false;
				for(auto layout = this->menuLayouts->begin() ; layout < this->menuLayouts->end(); layout++){
					if ((*layout)->MenuID() == gfxReturn.Int()){
						delete this->menu;
						this->menu = new GFXInterface::GFXMenu(system,this->configList,(*layout),addons);
						found = true;
						break;
					}
				}
				//If Not Found
				if (found == false)	LOGSYSTEM->Error("GOTO Menu not found");
				break;
			}
			default:
				break;
			}
		}
	}
	//if while loop where to ever fail return nothing or if the menu ID was not found.
	return ReturnData(MMNothing);
}

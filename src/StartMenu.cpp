/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "StartMenu.h"

StartMenu::StartMenu(SystemInterface::System* system):system(system) {
	OSData::File* file = NULL;

	if(Functions::FolderExists("Data")){
		if (Functions::FileExists("Data/StartMenu.xml"))
			file = new OSData::File("Data/StartMenu.xml");
		else if (Functions::FileExists("Data/StartMenu.dat"))
			file = new OSData::File("Data/StartMenu.dat");

		this->layout = file->ReturnMenuLayout();
		file->KeepData();
		this->menu = new GFXInterface::GFXMenu(system,this->layout);
		delete file;
	}
}

StartMenu::~StartMenu() {
	delete this->layout;
}

GFXInterface::GFXReturn StartMenu::Loop(){
	if (this->layout == NULL){
		LOGSYSTEM->Error("Start Menu File not found Exiting!");
		return GFXInterface::GFXReturn(MMQuit);
	}
	GFXInterface::GFXReturn gfxReturn = GFXInterface::GFXReturn(MMNothing);
	while (true){
		gfxReturn = this->menu->Loop();
		switch(gfxReturn.MenuEvent()){
		case MMStartGame:
		case MMQuit:
			return gfxReturn;
    	default:
    		break;
		}
	}
	return GFXInterface::GFXReturn(MMNothing);
}

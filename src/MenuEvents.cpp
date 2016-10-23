/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MenuEvents.h"

std::string MenuEventToString(eMenuEvent event){
	switch(event){
	case MMStartMenu:
		return "StartMenu";
	case MMStartGame:
		return "StartGame";
	case MMMapEditor:
		return "MapEditor";
	case MMGameOptions:
		return "GameOptions";
	case MMAddGame:
		return "AddGame";
	case MMCreateGame:
		return "CreateGame";
	case MMEditGame:
		return "EditGame";
	case MMOptions:
		return "Options";
	case MMAbout:
		return "About";
	case MMQuit:
		return "Quit";
	case MMNothing:
	default:
		return "Nothing";
	}
}

eMenuEvent GetMenuEvent(std::string data){
	if(data == "StartMenu") return MMStartMenu;
	if(data == "StartGame") return MMStartGame;
	if(data == "MapEditor") return MMMapEditor;
	if(data == "GameOptions") return MMGameOptions;
	if(data == "AddGame") return MMAddGame;
	if(data == "CreateGame") return MMCreateGame;
	if(data == "EditGame") return MMEditGame;
	if(data == "Options") return MMOptions;
	if(data == "About") return MMAbout;
	if(data == "Quit") return MMQuit;

	//if(data == "Nothing")
	return MMNothing;
}

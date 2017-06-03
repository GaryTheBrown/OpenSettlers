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
	case MMNothing:
		return "Nothing";
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
	case GMGotoMenu:
		return "GoToMenu";
	case CLDisplayAll:
		return "UpdateDisplay";
	case CLSingleOption:
		return "SingleOption";
	default:
		return "";
	}
}

eMenuEvent GetMenuEvent(std::string data){
	if(data == "Nothing")			return MMNothing;
	if(data == "StartMenu")			return MMStartMenu;
	if(data == "StartGame")			return MMStartGame;
	if(data == "MapEditor")			return MMMapEditor;
	if(data == "GameOptions")		return MMGameOptions;
	if(data == "AddGame")			return MMAddGame;
	if(data == "CreateGame")		return MMCreateGame;
	if(data == "EditGame")			return MMEditGame;
	if(data == "Options")			return MMOptions;
	if(data == "About")				return MMAbout;
	if(data == "Quit")				return MMQuit;
	if(data == "GoToMenu")			return GMGotoMenu;
	if(data == "UpdateDisplay")		return CLDisplayAll;
	if(data == "ChangeOption")		return CLSingleOption;

	//if not found return MMNothing
	return MMNothing;
}

eReturnExtra MenuEventReturnType(eMenuEvent menuEvent){
		switch(menuEvent){

		case MMAbout:
		case MMAddGame:
		case MMCreateGame:
		case MMEditGame:
		case MMGameOptions:
		case MMMapEditor:
		case MMNothing:
		case MMOptions:
		case MMQuit:
		case MMStartGame:
		case MMStartMenu:
		case CLDisplayAll:
		default:
			return RDNone;

		case GMGotoMenu:
			return RDInt;
		case CLSingleOption:
			return RDString;
		}
		return RDNone;
}

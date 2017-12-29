/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef MENUEVENT_H
#define MENUEVENT_H
#include <string>

enum eMenuEvent {
	//These return nothing
		MMNothing,
		MMStartMenu,
		MMStartGame,
		MMMapEditor,
		MMGameOptions,
		MMAddGame,
		MMCreateGame,
		MMEditGame,
		MMOptions,
		MMAbout,
		MMQuit,

		GMGotoMenu,//Return Int

		CLDisplayAll,
		CLSingleOption,//Return String



		};//{Nothing,Quit,StartGame,About,Options,PlayGame,LoadGame,SaveGame,OpenMenu,OpenWindow,CloseWindow,LoadInternalData, TestData,SaveData};

enum eReturnExtra : unsigned char {
	RDNone = 0,
	RDInt = 1,
	RDString = 2
};

extern std::string MenuEventToString(eMenuEvent event);
extern eMenuEvent GetMenuEvent(std::string data);
extern eReturnExtra MenuEventReturnType(eMenuEvent menuEvent);

#endif
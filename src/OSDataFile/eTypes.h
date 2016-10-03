/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once

namespace OSData{

	enum eBuildingType: unsigned char{
		HEADBUILDING,
		HEADResource,
		HEADProduction,
		HEADMilitary,
		HEADSpecial,
		InternalResource,
		NaturalResource,
		FarmedResource,
		ResourceProduction,
		MachineProduction,
		SettlerProduction
	};

	enum eSettlerType: unsigned char{
		BASE,
		Free,
		Carrier,
		Builder,
		Leveler,
		Buildingworker,
		Pioneer,
		Geologyst,
		Thief,
		Priest,
		LongRangeSoldier,
		ShortRangeSoldier
	};

	enum eMachineType: unsigned char{
		BASEMachine,
		AIRMachine
	};

	enum eMenuEvent: unsigned char{
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
		MMQuit
	};//{Nothing,Quit,StartGame,About,Options,PlayGame,LoadGame,SaveGame,OpenMenu,OpenWindow,CloseWindow,LoadInternalData, TestData,SaveData};

	enum eBoxType: unsigned char{
		Empty,
		GridView,
		ListView,
		FreeView
	};
}

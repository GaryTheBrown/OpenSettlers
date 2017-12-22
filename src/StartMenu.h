/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include "ConfigList.h"
#include "SystemInterface/System.h"

#include "MenuEvents.h"

#include "GFXInterface/GFXMenu.h"
#include "ReturnData.h"
#include "OSDataFile/OSDataFile.h"
#include "OSDataFile/FileTypes/Layout/MenuLayout.h"


class StartMenu {
private:
	SystemInterface::System* system;
	ConfigList* configList;
	GFXInterface::GFXMenu* menu = NULL;
	OSData::MenuLayout* layout = NULL;

public:
	StartMenu(SystemInterface::System* system,ConfigList* configList);
	virtual ~StartMenu();

	bool Load();
	OSData::MenuLayout* CreateLayout();
	ReturnData Loop();
};

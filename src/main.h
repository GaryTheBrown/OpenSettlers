/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef MAIN_H
#define MAIN_H

//STD Libraries
#include <string>
#include <iostream>

//config from autotools
#include "config.h"

//Log System
#include "Log.h"

//Startup Arguments
#include "StartupArguments.h"

//Config List
#include "ConfigList.h"
#include "ConfigTemplate.h"
//#include "ConfigFile.h"

//Converter
#include "Converter/Converter.h"
//Extractor
#include "Extractor/Extractor.h"

//System Interface
#include "SystemInterface/System.h"
#include "SystemInterface/SDL2/SDL2System.h"
#include "SystemInterface/OGL21/OGL21System.h"

#include "StartMenu.h"
#include "MenuEvents.h"
#include "OSDataFile/OSDataFile.h"

#include "Game/Game.h"
#include "ReturnData.h"

//Main Entry Point
extern int main(int argc, char *argv[]);

#endif
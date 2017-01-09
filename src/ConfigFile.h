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

#include "Functions/File/Functions.h"
#include "Functions/File/TextFile.h"
#include "Functions/File/Save.h"
#include "Functions/To.h"
#include "Log.h"

class ConfigFile {
	private:
		//Defaults (consts)
		const std::string DEFAULT_Location = "Config.cfg";
		//const std::string DEFAULT_Location = "~/OpenSettlers/Config.cfg";

		const bool DEFAULT_Fullscreen = false;
		const std::pair<int,int> DEFAULT_WindowSize = std::make_pair(800,600);

		bool fileOK = true;
		bool configChanged = false;

		//Config Settings with default options (expand into sections)
		std::string location = DEFAULT_Location;
		bool fullscreen = DEFAULT_Fullscreen;
		std::pair<int,int> windowSize = DEFAULT_WindowSize;




	public:
		ConfigFile(std::string file = "");
		virtual ~ConfigFile();

		bool ReadConfigFile(std::string file);

		//Get
		bool Fullscreen(){return this->fullscreen;};
		std::pair<int,int> WindowSize(){return this->windowSize;};

		//Set
		void SetFullscreen(bool fullscreen = true){this->fullscreen = fullscreen;};
		void SetWindowSize(std::pair<int,int>){this->windowSize = windowSize;};
};

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

//Include
#include <string>
#include <stdio.h>
#include <utility>
#include "../../ConfigList.h"
#include "../../MenuEvents.h"
#include "../../SystemInterface/System.h"
#include "../../SystemInterface/ImageContainer.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/GUIButtonData.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/ImageData.h"
#include "../../OSDataFile/FileTypes/GameData.h"
#include "../../ReturnData.h"
#include "GFXItem.h"

namespace GFXInterface {
	class GFXButton : public GFXItem{
	private:
		OSData::GUIButtonData* buttonData;
		std::string text;
		std::pair<int,int> textLocation;
		SystemInterface::ImageContainer* pressed = NULL;
		SystemInterface::ImageContainer* hover = NULL;
		SystemInterface::ImageContainer* textImage = NULL;
		std::pair<int,int> textSize;
		bool uniqueImage;
		bool selectable;
		bool clicked;
		bool selected;
		//ReturnData call;

		//TextCorrection
		void TextCorrection();
	public:

		//Constructor
		GFXButton(SystemInterface::System* system, ConfigList* configList, OSData::GUIButtonData* buttonData, OSData::GameAddons addons);
		virtual ~GFXButton();

		//Getters
		std::string GetText(){return this->text;}
		//ReturnData Call(){return this->call;}
		bool Selected(){return this->selected;}

		//Setters
		void SetLocation(std::pair<int,int> location);
		void SetSize(std::pair<int,int> size);

		//functions
		void Pressed();
		void Unselect();
		bool Released();

		void Draw();
		void CalculateLocation(std::pair<int,int> location = {0,0},std::pair<int,int> windowSize = {0,0});
		ReturnData EventHandler();


	};
}

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
#include "../../MenuEvents.h"
#include "../../SystemInterface/System.h"
#include "../../SystemInterface/ImageContainer.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/GUIButtonData.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/ImageData.h"
#include "../GFXReturn.h"
#include "GFXItem.h"


namespace GFXInterface {
	class GFXButton : public GFXItem{
	private:
		OSData::GUIButtonData* buttonData;
		std::string text;
		std::pair<int,int> textLocation;
		SystemInterface::ImageContainer* pressed;
		SystemInterface::ImageContainer* hover;
		SystemInterface::ImageContainer* textImage;
		std::pair<int,int> textSize;
		bool uniqueImage;
		bool selectable;
		bool clicked;
		bool selected;
		eMenuEvent call;

	public:

		//Constructor
		GFXButton(SystemInterface::System* system, OSData::GUIButtonData* buttonData);
		virtual ~GFXButton();

		//Getters
		virtual	std::string GetText(){return this->text;}
		eMenuEvent Call(){return this->call;}
		virtual bool Selected(){return this->selected;}

		//Setters
		virtual void SetLocation(std::pair<int,int> location);
		virtual void SetSize(std::pair<int,int> size);

		//functions
		void Pressed();
		void Unselect();
		bool Released();

		virtual void Draw();
		virtual void CalculateLocation(std::pair<int,int> location = {0,0},std::pair<int,int> windowSize = {0,0});
		virtual eMenuEvent EventHandler();


	};
}

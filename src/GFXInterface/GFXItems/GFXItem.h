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
#include <utility>

#include "../../SystemInterface/System.h"
#include "../../SystemInterface/ImageContainer.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/GUIItemData.h"
#include "../GFXReturn.h"

namespace GFXInterface {
	class GFXItem {
	private:
		OSData::GUIItemData* itemData;
		OSData::GUIItemData::eGUIItemType itemType;

		bool temp = false;
	protected:
		SystemInterface::System* system;
		SystemInterface::ImageContainer* image;
		std::pair<int,int> location;
		std::pair<int,int> size;
		//TODO THE BOOLS BELOW NEED FUNCTIONS TO WORK WITH THEM
		//visible ->Show(true)+Hide(false)
		//enable ->enable(true)+disable(false)
		//some why of mass disabling of buttons
		//bool Visible
		//bool enabled

	public:
		GFXItem(SystemInterface::System* system, OSData::GUIItemData::eGUIItemType itemType, OSData::GUIItemData* itemData);
		virtual ~GFXItem();

		//Getters
		virtual std::string GetText(){return "";};
		OSData::GUIItemData::eGUIItemType GetItemType(){return this->itemType;}
		std::pair<int,int> GetSize(){return this->size;}
		std::pair<int,int> GetLocation(){return this->location;}
		virtual GFXItem* GetSelected(){return NULL;}
		virtual bool Selected(){return false;}

		//Setters
		virtual void SetLocation(std::pair<int,int> location){this->location = location;}
		virtual void SetSize(std::pair<int,int> size) {this->size = size;}

		virtual void CalculateLocation(std::pair<int,int> location = {0,0},std::pair<int,int> windowSize = {0,0});
		virtual void Draw(){};

		virtual eMenuEvent EventHandler(){return MMNothing;}

		bool IsMouseOver();
	};
}

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
#include <utility>
#include <libxml/tree.h>

#include "../../../../MenuEvents.h"
#include "../../../../Functions/Image/RGBA.h"
#include "../../../../Functions/Image/RGBImage.h"
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/To.h"
#include "../../../../GFXInterface/GFXReturn.h"
#include "../../../APILEVELS.h"
#include "../../FileTypes.h"
#include "GUIItemData.h"
#include "ImageData.h"
//TODO ALLOW TEXT TO CHANGE COLOUR ADDING IN 2 more textures that will draw in the 3 states up pressed and down GFXButton Needs 2 more containers as well
namespace OSData{
	class GUIButtonData : public GUIItemData {
	private:
		std::string text = "";
		RGBA textColour = 0xFFFFFFFF;
		signed short fontSize = 0;
		signed short textBuffer = 0;
		ImageData image;
		ImageData hover;
		ImageData pressed;
		eMenuEvent menuEvent = MMNothing;
		bool multiSelect = false;

		void CheckValues(std::string name, std::string value);
	public:
		GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition horizontalPosition,ePosition verticalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,std::string imageLocation,std::string pressedLocation,std::string hoverLocation,eMenuEvent menuEvent,bool multiSelect);
		GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition horizontalPosition,ePosition verticalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,signed int imageNumber,signed int pressedNumber,signed int hoverNumber,eMenuEvent menuEvent,bool multiSelect);
		GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition horizontalPosition,ePosition verticalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,RGBA buttonColour,RGBA pressedButtonColour,RGBA hoverButtonColour,eMenuEvent menuEvent,bool multiSelect);
		GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition horizontalPosition,ePosition verticalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,Functions::RGBImage* button,Functions::RGBImage* pressedButton,Functions::RGBImage* hoverButton,eMenuEvent menuEvent,bool multiSelect);
		GUIButtonData(Functions::DataReader* reader);
		GUIButtonData(xmlNode* node);
		virtual ~GUIButtonData(){};

		std::string Text(){return this->text;}
		RGBA TextColour(){return this->textColour;}
		signed short FontSize(){return this->fontSize;}
		signed short TextBuffer(){return this->textBuffer;}

		ImageData Image(){return this->image;}
		ImageData Hover(){return this->hover;}
		ImageData Pressed(){return this->pressed;}

		eMenuEvent MenuEvent(){return this->menuEvent;}
		bool MultiSelect(){return this->multiSelect;}

		bool ToSaveToData(std::vector<char>* data = NULL);
		bool ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations = NULL);
		bool LinkNumbers(std::vector<Functions::RGBImage*>* images);
		std::string ToString();
	};
}

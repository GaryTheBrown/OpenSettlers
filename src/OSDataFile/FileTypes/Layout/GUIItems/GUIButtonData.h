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
#include <string>
#include <vector>
#include <utility>

#include "../../../../Functions/Image/RGBA.h"
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/File/TextLoad.h"
#include "../../../../Functions/To.h"
#include "../../../APILEVELS.h"
#include "../../../eTypes.h"
#include "../../FileTypes.h"

#include "GUIItemData.h"

namespace OSData{
	class GUIButtonData : public GUIItemData {
	private:
		std::string text;
		RGBA textColour;
		signed short fontSize;
		signed short textBuffer;

		std::string imageLocation = "";
		unsigned int imageNumber = 0;
		std::string hoverImageLocation = "";
		unsigned int hoverImageNumber = 0;
		std::string pressedImageLocation = "";
		unsigned int pressedImageNumber = 0;
		RGBA buttonColour;
		RGBA pressedButtonColour;
		RGBA hoverButtonColour;
		eMenuEvent menuEvent;
		bool multiSelect;

	public:

		GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,unsigned int imageNumber,unsigned int pressedNumber,unsigned int hoverNumber,eMenuEvent menuEvent,bool multiSelect);
		GUIButtonData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition,std::string text,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,RGBA buttonColour,RGBA pressedButtonColour,RGBA hoverButtonColour,eMenuEvent menuEvent,bool multiSelect);
		GUIButtonData(Functions::DataReader* reader);
		GUIButtonData(std::string line);
		virtual ~GUIButtonData(){};

		std::string Text(){return this->text;}
		RGBA TextColour(){return this->textColour;}
		signed short FontSize(){return this->fontSize;}
		signed short TextBuffer(){return this->textBuffer;}
		std::string ImageLocation(){return this->imageLocation;}
		std::string HoverLocation(){return this->hoverImageLocation;}
		std::string PressedLocation(){return this->pressedImageLocation;};
		unsigned int ImageNumber(){return this->imageNumber;}
		unsigned int HoverNumber(){return this->hoverImageNumber;}
		unsigned int PressedNumber(){return this->pressedImageNumber;};
		RGBA ButtonColour(){return this->buttonColour;}
		RGBA HoverButtonColour(){return this->hoverButtonColour;}
		RGBA PressedButtonColour(){return this->pressedButtonColour;}
		eMenuEvent MenuEvent(){return this->menuEvent;}
		bool MultiSelect(){return this->multiSelect;}

		std::string ToSaveToText();
		bool ToSaveToData(std::vector<char>* data = NULL);
	};
}

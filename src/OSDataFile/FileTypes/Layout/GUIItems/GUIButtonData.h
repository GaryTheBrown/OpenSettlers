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
#include "../../../../ReturnData.h"
#include "../../../APILEVELS.h"
#include "../../FileTypes.h"
#include "ExtraData/GUIButtonTypeData.h"
#include "GUIItemData.h"
#include "ImageData.h"

namespace OSData{
	class GUIButtonData : public GUIItemData {
	public:

	private:
		std::string text = "";
		RGBA textColour = 0xFFFFFFFF;
		unsigned short fontSize = 10;
		ImageData image;
		ImageData hover;
		ImageData pressed;
		GUIButtonTypeData buttonType = GUIButtonTypeData(GUIButtonTypeData::eNone);
		ReturnData returnData = MMNothing;
		bool multiSelect = false;

		void CheckValues(std::string name, std::string value);
		void GetButtonType(std::string value);
		std::string ButtonTypeString();
	public:

		GUIButtonData(GUIItemData baseData,std::string text,RGBA textColour,unsigned short fontSize, ImageData image, ImageData pressed,ImageData hover,GUIButtonTypeData buttonType,ReturnData returnData,bool multiSelect);
		GUIButtonData(Functions::DataReader* reader);
		GUIButtonData(xmlNode* node);
		virtual ~GUIButtonData(){};

		std::string Text(){return this->text;}
		RGBA TextColour(){return this->textColour;}
		unsigned short FontSize(){return this->fontSize;}

		ImageData Image(){return this->image;}
		ImageData Hover(){return this->hover;}
		ImageData Pressed(){return this->pressed;}
		GUIButtonTypeData ButtonType(){return this->buttonType;}
		ReturnData MenuEvent(){return this->returnData;}
		bool MultiSelect(){return this->multiSelect;}

		bool ToSaveToData(std::vector<char>* data = NULL);
		bool ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations = NULL);
		bool LinkNumbers(std::vector<Functions::RGBImage*>* images);
		std::string ToString();
	};
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef OSDATAFILE_FILETYPES_LAYOUT_GUIITEMS_GUIBUTTONDATA_H
#define OSDATAFILE_FILETYPES_LAYOUT_GUIITEMS_GUIBUTTONDATA_H

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
#include "GUIButtonTypeData.h"
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
		explicit GUIButtonData(Functions::DataReader* reader);
		explicit GUIButtonData(xmlNode* node);
		virtual ~GUIButtonData(){};

		const std::string Text(){return this->text;}
		const RGBA TextColour(){return this->textColour;}
		const unsigned short FontSize(){return this->fontSize;}

		ImageData Image(){return this->image;}
		ImageData Hover(){return this->hover;}
		ImageData Pressed(){return this->pressed;}
		const GUIButtonTypeData ButtonType(){return this->buttonType;}
		const ReturnData MenuEvent(){return this->returnData;}
		const bool MultiSelect(){return this->multiSelect;}

		bool ToSaveToData(std::vector<char>* data = NULL);
		bool ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations = NULL);
		bool LinkNumbers(std::vector<Functions::RGBImage*>* images);
		std::string ToString();
	};
}

#endif
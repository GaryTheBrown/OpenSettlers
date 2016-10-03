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
#include "../../FileTypes.h"

#include "GUIItemData.h"
#include "GUIButtonData.h"
#include "GUIImageData.h"
#include "GUITextData.h"

namespace OSData{
	class GUIBoxData : public GUIItemData {
	private:
		RGBA backgroundColour;
		eBoxType boxType;
		bool multiSelect;



	public:
		std::vector<GUIItemData*>* itemData;

		GUIBoxData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition, RGBA backgroundColour, eBoxType boxType, std::vector<GUIItemData*>* itemDataList,bool multiSelect = false);
		GUIBoxData(Functions::DataReader* reader);
		GUIBoxData(std::string line);
		virtual ~GUIBoxData(){};

		RGBA BackgroundColour(){return this->backgroundColour;}
		eBoxType BoxType(){return this->boxType;}
		bool MultiSelect(){return this->multiSelect;}

		bool ToSaveToData(std::vector<char>* data = NULL);
	};
}

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
#include <algorithm>
#include <libxml/tree.h>

#include "../../../../Functions/Image/RGBA.h"
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/File/Functions.h"
#include "../../../../Functions/To.h"
#include "../../../APILEVELS.h"
#include "../../FileTypes.h"
#include "ExtraData/GUIBoxDirectoryData.h"
#include "ExtraData/GUIButtonTypeData.h"
#include "GUIItemNew.h"
#include "GUIItemData.h"
#include "GUIButtonData.h"
#include "GUIImageData.h"
#include "GUITextData.h"
#include "GUISpacerData.h"


namespace OSData{
	class GUIBoxData : public GUIItemData{
	public:
		enum eBoxType: unsigned char{
			tEmpty = 0,
			tGridView = 1,
			tListView = 2,
			tFreeView = 3,
			tListFullDir = 4,
			tListFileDir = 5,
			tListFolderDir = 6
		};
	private:
		//TODO replace background colour with imageData.
		RGBA backgroundColour = 0x000000FF;
		eBoxType boxType = tEmpty;
		bool multiSelect = false;
		GUIBoxDirectoryData* directoryData = NULL;
		std::vector<GUIItemData*>* itemData = NULL;

		void GetBoxType(std::string data);
		void GetBoxFunction(std::string data);
		void CheckValues(std::string name, std::string value);
		void DirCreation();
	public:

		GUIBoxData(GUIItemData baseData, RGBA backgroundColour, eBoxType boxType, std::vector<GUIItemData*>* itemDataList,bool multiSelect = false);
		GUIBoxData(Functions::DataReader* reader);
		GUIBoxData(xmlNode* node);
		virtual ~GUIBoxData();

		RGBA BackgroundColour(){return this->backgroundColour;}
		eBoxType BoxType(){return this->boxType;}
		bool MultiSelect(){return this->multiSelect;}
		std::vector<GUIItemData*>* ItemData(){return this->itemData;};

		bool ToSaveToData(std::vector<char>* data = NULL);
		bool ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations = NULL);
		bool LinkNumbers(std::vector<Functions::RGBImage*>* images);
		std::string ToString();
	};
}

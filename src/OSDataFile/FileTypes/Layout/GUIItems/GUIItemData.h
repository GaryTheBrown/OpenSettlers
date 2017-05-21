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
#include <vector>
#include <libxml/tree.h>

#include "../../../../Functions/Image/RGBImage.h"
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/To.h"
#include "../../../APILEVELS.h"
#include "GUIVisibilityData.h"


namespace OSData{
	class GUIItemData {
	public:
		enum eGUIItemType: unsigned char{
			GUINoneType = 0,
			GUIImageType = 1,
			GUIButtonType = 2,
			GUITextType = 3,
			GUIBoxType = 4,
			GUISpacerType = 5
		};

		enum ePosition: unsigned char{
			pNone = 0,
			AlignLeft = 1,
			AlignTop = 1,
			AlignRight = 2,
			AlignBottom = 2,
			AlignCentre = 3,
			FullTile = 4,
			FullStretch = 5,
			StretchSetSize = 6,//stretches from x from top/left for x size
			StretchFromFrom = 7, //stretches from x from top/left to x from bottom/right
			StretchPercent = 8,
			AlignTL = (AlignLeft|AlignTop),
			AlignBR = (AlignRight|AlignBottom)
		};
	private:
		void CheckItemValues(std::string name, std::string value);
	protected:
		eGUIItemType itemType;
		std::pair<unsigned short,unsigned short> location = {0,0};
		std::pair<unsigned short,unsigned short> size = {0,0};
		ePosition horizontalPosition = pNone;
		ePosition verticalPosition = pNone;
		GUIVisibilityData visibilityData = GUIVisibilityData(OSData::GUIVisibilityData::vNone);

		bool fileOK = true;
		unsigned int APIVersion = APILEVEL::GUIITEMS;

		ePosition GetPositionType(std::string data);
	public:
		GUIItemData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size, ePosition horizontalPosition, ePosition verticalPosition,GUIVisibilityData visibilityData);
		GUIItemData(eGUIItemType itemType,GUIItemData baseData);
		GUIItemData(eGUIItemType itemType,Functions::DataReader* reader);
		GUIItemData(eGUIItemType itemType,xmlNode* node);
		virtual ~GUIItemData(){};

		eGUIItemType ItemType(){return this->itemType;}
		std::pair<unsigned short,unsigned short> Location(){return this->location;}
		std::pair<unsigned short,unsigned short> Size(){return this->size;}
		ePosition Vertical(){return this->verticalPosition;}
		ePosition Horizontal(){return this->horizontalPosition;}
		GUIVisibilityData VisibilityData(){return this->visibilityData;}

		virtual bool ToSaveToData(std::vector<char>* data = NULL);
		virtual bool ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations = NULL){return true;};
		virtual bool LinkNumbers(std::vector<Functions::RGBImage*>* images){return true;};
		virtual std::string ToString();
	};
}

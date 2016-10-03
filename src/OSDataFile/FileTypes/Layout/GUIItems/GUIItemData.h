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

#include "../../../../Functions/File/TextLoad.h"
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/To.h"
#include "../../../APILEVELS.h"
#include "../../../../Log.h"

namespace OSData{
	class GUIItemData {
	public:
		enum eGUIItemType: unsigned char{
			GUINoneType,
			GUIImageType,
			GUIButtonType,
			GUITextType,
			GUIBoxType
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
			AlignBR = (AlignRight|AlignTop)
		};

	protected:
		bool fileOK = true;

		unsigned int APIVersion = APILEVEL::GUIITEMS;
		eGUIItemType itemType;
		std::pair<unsigned short,unsigned short> location;
		std::pair<unsigned short,unsigned short> size;
		ePosition verticalPosition;
		ePosition horizontalPosition;

	public:
		GUIItemData(eGUIItemType itemType,std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size, ePosition verticalPosition, ePosition horizontalPosition);
		GUIItemData(eGUIItemType itemType,Functions::DataReader* reader);
		GUIItemData(eGUIItemType itemType,std::string line);
		virtual ~GUIItemData(){};

		eGUIItemType ItemType(){return this->itemType;}
		ePosition Vertical(){return this->verticalPosition;}
		ePosition Horizontal(){return this->horizontalPosition;}
		std::pair<unsigned short,unsigned short> GetLocation(){return this->location;}
		std::pair<unsigned short,unsigned short> GetSize(){return this->size;}

		virtual bool ToSaveToData(std::vector<char>* data = NULL);
	};
}

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
#include <algorithm>

#include "../../../../Functions/Image/RGBA.h"
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/File/TextLoad.h"
#include "../../../../Functions/To.h"
#include "../../../APILEVELS.h"
#include "../../FileTypes.h"

#include "GUIItemData.h"

namespace OSData{
	class GUITextData : public GUIItemData {
	private:
		std::string text;
		RGBA textColour;
		signed short fontSize;

	public:
		GUITextData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition,std::string text,RGBA textColour,signed short fontSize);
		GUITextData(Functions::DataReader* reader);
		GUITextData(std::string line);
		virtual ~GUITextData();

		std::string Text(){return text;}
		RGBA TextColour(){return textColour;}
		signed short FontSize(){return fontSize;}

		bool ToSaveToData(std::vector<char>* data = NULL);
	};
}

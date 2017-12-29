/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef OSDATAFILE_FILETYPES_LAYOUT_GUIITEMS_GUITEXTDATA_H
#define OSDATAFILE_FILETYPES_LAYOUT_GUIITEMS_GUITEXTDATA_H

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <libxml/tree.h>

#include "../../../../Functions/Image/RGBA.h"
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/To.h"
#include "../../../APILEVELS.h"
#include "../../FileTypes.h"
#include "GUIItemData.h"

namespace OSData{
	class GUITextData : public GUIItemData {
	private:
		std::string text = "";
		RGBA textColour = 0xFFFFFFFF;
		signed short fontSize = 0;

		void CheckValues(std::string name, std::string value);
	public:
		GUITextData(GUIItemData baseData,std::string text,RGBA textColour,signed short fontSize);
		explicit GUITextData(Functions::DataReader* reader);
		explicit GUITextData(xmlNode* node);
		virtual ~GUITextData(){};

		const std::string Text(){return text;}
		const RGBA TextColour(){return textColour;}
		const signed short FontSize(){return fontSize;}

		bool ToSaveToData(std::vector<char>* data = NULL);
		std::string ToString();
	};
}

#endif
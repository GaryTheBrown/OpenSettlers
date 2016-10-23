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

#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/To.h"

#include "../../../APILEVELS.h"
#include "../../FileTypes.h"
#include "GUIItemData.h"


namespace OSData{
	class GUISpacerData : public GUIItemData {
	private:

		void CheckValues(std::string name, std::string value);
	public:
		GUISpacerData(std::pair<unsigned short,unsigned short> size);
		GUISpacerData(Functions::DataReader* reader);
		GUISpacerData(xmlNode* node);
		virtual ~GUISpacerData(){};

		bool ToSaveToData(std::vector<char>* data = NULL);
		std::string ToString();
	};
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef OSDATAFILE_FILETYPES_LAYOUT_GUIITEMS_GUIVISIBILITYDATA_H
#define OSDATAFILE_FILETYPES_LAYOUT_GUIITEMS_GUIVISIBILITYDATA_H

#include <string>
#include <vector>
#include <libxml/tree.h>

#include "../../../../Functions/File/DataReader.h"
#include "../../GameData.h"
namespace OSData{
	class GUIVisibilityData {
	public:
		enum VisibilityOptions: unsigned char{
			vNone = 0,
			vBasic = 1,
			vAddonRequired = 2
		};

	private:
		VisibilityOptions type = vNone;
		bool visible = true;
		bool enabled = true;
		OSData::GameAddons addonRequired = eS2None;

	public:
		GUIVisibilityData();
		explicit GUIVisibilityData(VisibilityOptions type);
		GUIVisibilityData(VisibilityOptions type, bool visible, bool enabled);
		GUIVisibilityData(VisibilityOptions type, OSData::GameAddons addonRequired);
		explicit GUIVisibilityData(Functions::DataReader* reader);
		~GUIVisibilityData(){};

		const VisibilityOptions Type(){return this->type;};
		const bool Visible(){return this->visible;};
		const bool Enabled(){return this->enabled;};
		const OSData::GameAddons AddonRequired(){return this->addonRequired;};

		void CheckItemValues(std::string name, std::string value);
		bool ToSaveToData(std::vector<char>* data = NULL);
		std::string ToString();

	};
}

#endif
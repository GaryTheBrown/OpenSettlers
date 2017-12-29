/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef OSDATAFILE_FILETYPES_LAYOUT_GUIITEMS_GUIITEMNEW_H
#define OSDATAFILE_FILETYPES_LAYOUT_GUIITEMS_GUIITEMNEW_H

#include <string>
#include <libxml/tree.h>

#include "../../../../Functions/File/DataReader.h"
#include "GUIItemData.h"
#include "GUIBoxData.h"
#include "GUIButtonData.h"
#include "GUIImageData.h"
#include "GUITextData.h"
#include "GUISpacerData.h"

namespace OSData{
	extern GUIItemData::eGUIItemType GetItemType(std::string data);
	extern OSData::GUIItemData* DoItemType(GUIItemData::eGUIItemType itemDataType,void* data, bool xml = false);
}

#endif
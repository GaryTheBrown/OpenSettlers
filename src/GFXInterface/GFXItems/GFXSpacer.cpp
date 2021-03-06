/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GFXSpacer.h"

GFXInterface::GFXSpacer::GFXSpacer(SystemInterface::System* system, ConfigList* configList, OSData::GUISpacerData* spacerData)
			:GFXItem(system,configList,OSData::GUIItemData::GUISpacerType,  (OSData::GUIItemData*)spacerData,OSData::eS2None){
	this->spacerData = spacerData;
	this->location = this->spacerData->Location();
	this->size = this->spacerData->Size();
	this->CalculateLocation();
}

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

GFXInterface::GFXSpacer::GFXSpacer(SystemInterface::System* system, OSData::GUISpacerData* spacerData)
			:GFXItem(system,OSData::GUIItemData::GUISpacerType,(OSData::GUIItemData*)spacerData){
	this->spacerData = spacerData;
	this->location = this->spacerData->GetLocation();
	this->size = this->spacerData->GetSize();
	this->CalculateLocation();
}

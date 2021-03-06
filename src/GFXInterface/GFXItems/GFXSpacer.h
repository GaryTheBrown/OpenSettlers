/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef GFXINTERFACE_GFXITEMS_GFXSPACER_H
#define GFXINTERFACE_GFXITEMS_GFXSPACER_H

//Includes
#include <string>
#include <stdio.h>
#include <utility>
#include "../../ConfigList.h"
#include "../../SystemInterface/System.h"
#include "../../SystemInterface/ImageContainer.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/GUISpacerData.h"
#include "../../OSDataFile/FileTypes/GameData.h"
#include "GFXItem.h"

namespace GFXInterface {
	class GFXSpacer : public GFXItem{
	private:
		OSData::GUISpacerData* spacerData;
	public:
		GFXSpacer(SystemInterface::System* system, ConfigList* configList, OSData::GUISpacerData* spacerData);
		virtual ~GFXSpacer(){};

	};
}

#endif
/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef GFXINTERFACE_GFXITEMS_GFXIMAGE_H
#define GFXINTERFACE_GFXITEMS_GFXIMAGE_H

//Includes
#include <string>
#include <stdio.h>
#include <utility>
#include "../../ConfigList.h"
#include "../../SystemInterface/System.h"
#include "../../SystemInterface/ImageContainer.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/GUIImageData.h"
#include "../../OSDataFile/FileTypes/GameData.h"
#include "GFXItem.h"

namespace GFXInterface {
	class GFXImage : public GFXItem{
	private:
		OSData::GUIImageData* imageData;

	public:
		//constructors
		GFXImage(SystemInterface::System* system, ConfigList* configList, OSData::GUIImageData* imageData, OSData::GameAddons addons);
		virtual ~GFXImage(){};

		//functions
		void Draw();

	};
}

#endif
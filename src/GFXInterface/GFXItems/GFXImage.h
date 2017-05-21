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

//Includes
#include <string>
#include <stdio.h>
#include <utility>
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
		GFXImage(SystemInterface::System* system, OSData::GUIImageData* imageData, OSData::GameAddons addons);
		virtual ~GFXImage(){};

		//functions
		void Draw();

	};
}

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

//Include
#include <string>
#include <stdio.h>
#include <utility>

#include "../../Functions/Image/RGBA.h"
#include "../../SystemInterface/System.h"
#include "../../SystemInterface/ImageContainer.h"
#include "../../OSDataFile/FileTypes/Layout/GUIItems/GUITextData.h"
#include "GFXItem.h"

namespace GFXInterface {
	class GFXText : public GFXItem{
	private:
		OSData::GUITextData* textData;
	public:
		//constructors
		GFXText(SystemInterface::System* system, std::string text, RGBA textColour, std::pair<int,int> location);
		GFXText(SystemInterface::System* system, OSData::GUITextData* textData);
		virtual ~GFXText(){};

		virtual void Draw();
	};
}

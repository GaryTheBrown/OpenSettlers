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

#include "../../../../Functions/Image/RGBA.h"
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/File/TextLoad.h"
#include "../../../../Functions/To.h"
#include "../../../APILEVELS.h"
#include "../../FileTypes.h"
#include "GUIItemData.h"

namespace OSData{
	class GUIImageData : public GUIItemData {
	private:
		std::string imageLocation = "";
		unsigned short imageNumber = 0;

	public:
		GUIImageData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition verticalPosition,ePosition horizontalPosition,std::string imageLocation);
		GUIImageData(Functions::DataReader* reader);
		GUIImageData(std::string line);
		virtual ~GUIImageData(){};

		std::string ImageLocation(){return imageLocation;}

		bool ToSaveToData(std::vector<char>* data = NULL);

	};
}

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

#include "../../../../Functions/Image/RGBA.h"
#include "../../../../Functions/Image/RGBImage.h"
#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/To.h"

#include "../../../APILEVELS.h"
#include "../../FileTypes.h"
#include "GUIItemData.h"
#include "ImageData.h"

namespace OSData{
	class GUIImageData : public GUIItemData {
	private:
		ImageData image;

		void CheckValues(std::string name, std::string value);
	public:
		GUIImageData(GUIItemData baseData,std::string imageLocation);
		GUIImageData(GUIItemData baseData,Functions::RGBImage* image);
		GUIImageData(Functions::DataReader* reader);
		GUIImageData(xmlNode* node);
		virtual ~GUIImageData(){};

		ImageData Image(){return this->image;}

		bool ToSaveToData(std::vector<char>* data = NULL);
		bool ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations = NULL);
		bool LinkNumbers(std::vector<Functions::RGBImage*>* images);
		std::string ToString();
	};
}

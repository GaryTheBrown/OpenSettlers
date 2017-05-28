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
#include <utility>
#include <algorithm>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "../Functions/File/DataReader.h"
#include "../Functions/File/Functions.h"
#include "../Functions/File/Save.h"
#include "../Functions/Image/FileImage.h"
#include "../Functions/Image/RGBImage.h"
#include "../Functions/To.h"
#include "../Log.h"
#include "APILEVELS.h"
#include "FileTypes/FileTypes.h"
#include "FileTypes/GameType.h"
#include "FileTypes/Layout/MenuLayout.h"

namespace OSData{
	class File {
	private:
		unsigned int APIVersion = 0;
		FileTypes* dataType = NULL;
		std::vector<Functions::RGBImage*>* images = NULL;
		std::vector<std::string>* imageLocations = NULL;

		bool fileOK = true;
		bool imagesAreNumbers = false;
		bool keepData = false;
		bool keepImages = false;
		void ConstructFromDataFile(std::string file);
		void ConstructFromXMLFile(std::string file);
		FileTypes::eFileType GetFileType(std::string data);
		void DoFileType(FileTypes::eFileType fileType, void* data, bool xml = false);
		void LoadImagesFromFile(Functions::DataReader* reader);
		bool SaveImagesToData(std::vector<char>* data);

	public:
		explicit File(std::string file);
		explicit File(FileTypes* data);
		virtual ~File();

		bool ToSaveToXML();
		bool ToSaveToData(std::string file);
		bool ImageLocationsToNumbers();
		bool ImageDataToNumbers();
		std::string ToString();
		void KeepData(){this->keepData = true;};
		void KeepImages(){this->keepImages = true;};
		MenuLayout* ReturnMenuLayout();
		GameType* ReturnGameType();
	};
}

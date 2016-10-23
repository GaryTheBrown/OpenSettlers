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

#include "../../../../../Functions/Image/RGBA.h"
#include "../../../../../Functions/File/DataReader.h"
#include "../../../../../Functions/To.h"


namespace OSData{
	class GUIBoxDirectoryData{
	private:
		std::string folderLocation = "";
		unsigned short verticalSize = 25;
		RGBA textColour = 0xFFFFFFFF;
		signed short fontSize = 0;
		signed short textBuffer = 0;
		RGBA selectColour;

		void CheckValues(std::string name, std::string value);
	public:
		GUIBoxDirectoryData(std::string folderLocation,unsigned short verticalSize,RGBA textColour,unsigned short fontSize, unsigned short textBuffer,RGBA selectColour);
		GUIBoxDirectoryData(Functions::DataReader* reader);
		GUIBoxDirectoryData(xmlNode* node);
		virtual ~GUIBoxDirectoryData(){};

		unsigned short VerticalSize(){return this->verticalSize;};
		std::string FolderLocation(){return this->folderLocation;};
		RGBA TextColour(){return this->textColour;};
		signed short FontSize(){return this->fontSize;};
		signed short TextBuffer(){return this->textBuffer;};
		RGBA SelectColour(){return this->selectColour;};

		std::string ToSaveToText();
		bool ToSaveToData(std::vector<char>* data = NULL);
		std::string ToString();
	};
}

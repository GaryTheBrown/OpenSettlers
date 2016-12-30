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

#include "../../../../../Functions/File/DataReader.h"
#include "../../../../../Functions/To.h"
#include "../../../FileTypes.h"

namespace OSData{
	class GUIButtonTypeData{
	public:
		enum eType : unsigned char {
			eNone = 0,
			eAction = 1,
			eSwitchBool = 2
		};
	private:
		eType type = eNone;
		std::string text = "";
		RGBA textColour = 0xFFFFFFFF;
		unsigned short fontSize = 10;
		void GetButtonType(std::string value);
		void CheckValues(std::string name, std::string value);

	public:

		GUIButtonTypeData(eType type);
		GUIButtonTypeData(std::string type);
		GUIButtonTypeData(eType type,std::string text,RGBA textColour,unsigned short fontSize);
		GUIButtonTypeData(Functions::DataReader* reader);
		GUIButtonTypeData(xmlNode* node);
		virtual ~GUIButtonTypeData(){};

		eType Type(){return this->type;}

		std::string ButtonTypeString();
		std::string Text(){return this->text;}
		RGBA TextColour(){return this->textColour;}
		unsigned short FontSize(){return this->fontSize;}


		bool ToSaveToData(std::vector<char>* data = NULL);
		std::string ToString();
	};
}

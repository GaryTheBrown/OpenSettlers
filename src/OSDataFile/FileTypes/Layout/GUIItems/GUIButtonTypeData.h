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

#include "../../../../Functions/File/DataReader.h"
#include "../../../../Functions/To.h"
#include "../../FileTypes.h"

namespace OSData{
	class GUIButtonTypeData{
	public:
		enum eType : unsigned char {
			eNone = 0,
			eAction = 1,
			eChangeGlobalSetting = 2,
			eChangeSetting = 3,
		};

	private:
		eType type = eNone;
		std::string text = "";
		void GetButtonType(std::string value);
		void CheckValues(std::string name, std::string value);

	public:

		explicit GUIButtonTypeData(eType type);
		explicit GUIButtonTypeData(std::string type);
		GUIButtonTypeData(eType type,std::string text);
		explicit GUIButtonTypeData(Functions::DataReader* reader);
		explicit GUIButtonTypeData(xmlNode* node);
		virtual ~GUIButtonTypeData(){};

		const eType Type(){return this->type;}

		std::string ButtonTypeString();
		const std::string Text(){return this->text;}

		bool ToSaveToData(std::vector<char>* data = NULL);
		std::string ToString();
	};
}

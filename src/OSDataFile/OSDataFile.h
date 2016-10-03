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
#include "../Functions/File/DataReader.h"
#include "../Functions/File/Functions.h"
#include "../Functions/File/Save.h"
#include "../Functions/To.h"
#include "../Log.h"

#include "APILEVELS.h"

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "FileTypes/FileTypes.h"
#include "FileTypes/Layout/MenuLayout.h"

namespace OSData{
	class File {
	private:
		unsigned int APIVersion = APILEVEL::MASTER;
		unsigned short baseGame = 0;

		FileTypes* dataType = NULL;

		bool fileOK = true;

		void ConstructFromDataFile(std::string file);
		void ConstructFromXMLFile(std::string file);
	public:
		File(std::string file);
		virtual ~File();

		bool ToSaveToXML();
		bool ToSaveToData(std::string file);
	};
}

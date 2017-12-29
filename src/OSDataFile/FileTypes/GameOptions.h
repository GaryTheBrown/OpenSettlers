/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef OSDATAFILE_FILETYPES_GAMEOPTIONS_H
#define OSDATAFILE_FILETYPES_GAMEOPTIONS_H

#include <string>
#include <libxml/tree.h>

#include "GameData.h"
#include "FileTypes.h"

#include "../../Functions/File/DataReader.h"
#include "../../Log.h"

namespace OSData {
	class GameOptions : public FileTypes {
	private:


		void CheckValues(std::string name, std::string value);
		void DoFileType(FileTypes::eFileType fileType, void* data);
	public:
		GameOptions();
		explicit GameOptions(Functions::DataReader* reader);
		explicit GameOptions(xmlNode* node);

		virtual ~GameOptions();
	};
}

#endif
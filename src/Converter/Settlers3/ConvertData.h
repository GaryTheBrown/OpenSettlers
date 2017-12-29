/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef CONVERTER_CONVERTDATA_H
#define CONVERTER_CONVERTDATA_H

#include <string>
#include "../../Extractor/Settlers3/VersionCheck.h"
#include "../../OSDataFile/FileTypes/GameData.h"

namespace Converter {
	namespace Settlers3{
		struct Data {
		Extractor::Settlers3::VersionS3 version;
		std::string locationofFiles = "";
		std::string locationofSNDFiles = "";
		std::pair <std::string,std::string> SNDFileName;
		std::string locationofGFXFiles = "";
		std::pair <std::string,std::string> GFXFileName;
		std::string locationofMAPFiles = "";
		std::pair <std::string,std::string> MAPFileName;
		OSData::GameAddons addons = OSData::eS3None;
		};
	}
}

#endif
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
#include "../../Log.h"
#include "../../Functions/File/Functions.h"
#include "../../Functions/File/Run.h"
#include "../eType.h"
#include "VersionCheck.h"
#include "GFXDataType.h"
#include "SNDDataType.h"
#include "MAPDataType.h"

namespace Extractor{
	namespace Settlers3{
		class Extract{
		private:
			VersionS3 gameVersion = VersionNONE;
			std::string location = "";
			std::string locationExtra = "";
			std::string saveLocation;

			bool RAWGFXFileExtract(std::string *folder, std::string *file);
			bool RAWSNDFileExtract(std::string *folder, std::string *file);
			bool RAWMAPFileExtract(std::string *folder, std::string *file, MapType mapType = MT_UNKNOWN);
			void RAWGFXFolderExtract(std::string *folder);
			void RAWSNDFolderExtract(std::string *folder);
			void RAWMAPFolderExtract(std::string *folder, MapType mapType = MT_UNKNOWN);

		public:
			Extract(std::string *location,bool GOG,std::string *saveLocation);
			Extract(){};
			~Extract();

			bool FullRAWExtract();
			bool ManualExtract(eType fileType,std::string *location);
		};
	}
}

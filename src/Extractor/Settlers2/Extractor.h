/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
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
#include "../eType.h"
#include "../../Log.h"
#include "../../Functions/File/Functions.h"
#include "../../Functions/File/Run.h"
#include "LBMDataType.h"

namespace Extractor{
	namespace Settlers2{
		class Extract{
		private:
			enum VersionS2{
				VersionNONE,
				VersionS2CD,
				VersionS2MCD,
				VersionS2GOLD,
				VersionS2GOG,
				VersionS2DISCINSTALL,
				VersionS2MCDINSTALL,
				VersionS2GOLDINSTALL,
				VersionS2GOGINSTALL
			};


			VersionS2 gameVersion = VersionNONE;
			std::string location = "";
			std::string locationExtra = "";

			bool RAWLBMFileExtract(std::string folder, std::string file);

			void RAWLBMFolderExtract(std::string folder);

			void CheckGameVersion(bool GOG);

		public:
			Extract(std::string location,bool GOG);
			Extract(){};

			virtual ~Extract();

			bool FullRAWExtract();

			bool ManualExtract(eType fileType,std::string location);


		};
	}
}

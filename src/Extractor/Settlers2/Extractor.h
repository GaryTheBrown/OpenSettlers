/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS2_EXTRACTOR_H
#define EXTRACTOR_SETTLERS2_EXTRACTOR_H
#include <string>
#include "../../Log.h"
#include "../../Functions/File/Functions.h"
#include "../../Functions/File/Run.h"
#include "../eType.h"
#include "LBMDataType.h"
#include "BBMDataType.h"
#include "LSTDataType.h"
#include "IDXDATDataType.h"
#include "BOBDataType.h"
#include "MAP/MAPDataType.h"

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
			std::string saveLocation;

			bool RAWLBMFileExtract(std::string *folder, std::string *file);
			void RAWLBMFolderExtract(std::string *folder);

			bool RAWBBMFileExtract(std::string *folder, std::string *file);
			void RAWBBMFolderExtract(std::string *folder);

			bool RAWLSTFileExtract(std::string *folder, std::string *file);
			void RAWLSTFolderExtract(std::string *folder);

			bool RAWIDXFileExtract(std::string *folder, std::string *file);
			void RAWIDXFolderExtract(std::string *folder);

			bool RAWBOBFileExtract(std::string *folder, std::string *file);
			void RAWBOBFolderExtract(std::string *folder);

			bool RAWMAPFileExtract(std::string *folder, std::string *file);
			void RAWMAPFolderExtract(std::string *folder);

			void CheckGameVersion(bool GOG);

		public:
			Extract(std::string *location,bool GOG,std::string *saveLocation);
			Extract(std::string *saveLocation);
			Extract(){};
			~Extract();

			bool FullRAWExtract();
			bool ManualExtract(Extractor::eType fileType,std::string *location);
		};
	}
}

#endif
/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_SETTLERS3_EXTRACTOR_H_
#define EXTRACTOR_SETTLERS3_EXTRACTOR_H_

#include <string>

#include "../../Log.h"

#include "../../Functions/FileFunctions.h"
#include "../../Functions/FileRun.h"
#include "../../Functions/RemoveFolder.h"
#include "GFXDataType.h"
#include "SNDDataType.h"

namespace Extractor{
	namespace Settlers3{
		class Extract {
		private:
			unsigned char gameVersion = 0;
			std::string location = "";

			bool RAWGFXFileExtract(std::string folder, std::string file);
			bool RAWSNDFileExtract(std::string folder, std::string file);
			void RAWGFXFolderExtract(std::string folder);
			void RAWSNDFolderExtract(std::string folder);

		public:
			Extract(std::string location,bool GOG = false);
			virtual ~Extract();

			bool RAWExtract();

			enum VersionS3{
				VersionS3CD1,
				VersionS3CD2,
				VersionS3MCD1,
				VersionS3QOTA1,
				VersionS3GOLD1,
				VersionS3GOLD2,
				VersionS3GOG,
				VersionS3DISCINSTALL,
				VersionS3GOLDINSTALL,
				VersionS3GOGINSTALL
			};
			unsigned char GameVersion(){return this->gameVersion;};
		};
	}
}
#endif

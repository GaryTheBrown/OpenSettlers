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

namespace Extractor{
	namespace Settlers3{
		enum VersionS3{
			VersionNONE,
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

		enum MapType{
			MT_UNKNOWN,
			MT_ORIGINALMISSIONS,
			MT_MCDMISSIONS,
			MT_QOTAMISSIONS,
			MT_MULTI,
			MT_SINGLE,
			MT_TUTORIAL,
			MT_USER
		};

		extern VersionS3 CheckGameVersion(std::string location, bool GOG);
	}
}

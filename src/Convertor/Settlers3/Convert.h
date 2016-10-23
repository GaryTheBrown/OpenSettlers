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

#include "../../Log.h"
#include "../../LogSystem/LogSystem.h"
#include "../../Functions/File/Open.h"
#include "../../Functions/File/Functions.h"
#include "../../Functions/File/Run.h"
#include "../../Functions/Image/RGBA.h"
#include "../../Functions/Image/RGBImage.h"
#include "../../Extractor/Settlers3/VersionCheck.h"
#include "../../Extractor/Settlers3/GFXDataType.h"
#include "../../Extractor/Settlers3/MAPDataType.h"
#include "GUI/ConvertGUI.h"
#include "ConvertData.h"


namespace Converter {
	namespace Settlers3{
		class Convert {
		private:
			bool somethingToExtract = true;
			Data data;
			ConvertGUI* GUIFunctions;

			void SetupData();

		public:
			Convert(std::string locationofFiles, bool GOG);
			virtual ~Convert();
			bool DoConvert();
		};
	}
}

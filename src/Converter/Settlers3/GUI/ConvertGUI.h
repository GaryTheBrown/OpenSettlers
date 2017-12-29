/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef CONVERTER_SETTLERS3_GUI_CONVERTGUI_H
#define CONVERTER_SETTLERS3_GUI_CONVERTGUI_H

#include <string>
#include <utility>
#include <vector>

#include "../ConvertData.h"

#include "../../../Functions/Image/RGBA.h"
#include "../../../Functions/Image/RGBImage.h"
#include "../../../Extractor/Settlers3/GFXDataType.h"
#include "../../../OSDataFile/OSDataFile.h"
#include "../../../OSDataFile/FileTypes/Layout/MenuLayout.h"
#include "../../../OSDataFile/FileTypes/Layout/LoadingScreenLayout.h"
#include "../../../OSDataFile/FileTypes/Layout/GUIItems/GUIItemData.h"
#include "../../../OSDataFile/FileTypes/Layout/GUIItems/GUIImageData.h"
#include "../../../OSDataFile/FileTypes/Layout/GUIItems/GUITextData.h"
#include "../../../OSDataFile/FileTypes/Layout/GUIItems/GUIButtonData.h"
#include "../../../OSDataFile/FileTypes/Layout/GUIItems/GUIBoxData.h"
#include "../../../OSDataFile/FileTypes/Layout/GUIItems/GUISpacerData.h"
#include "../../../OSDataFile/FileTypes/Layout/GUIItems/GUIButtonTypeData.h"

namespace Converter {
	namespace Settlers3{
		class ConvertGUI{
		private:
			Data* data;
		public:
			explicit ConvertGUI(Data* data):data(data){};
			virtual ~ConvertGUI(){};

			//Main Menu And Loading Screen
			void Original(OSData::GameType* gameType);
			void MissionCD(OSData::GameType* gameType);
			void Amazon(OSData::GameType* gameType);
			void Gold(OSData::GameType* gameType);
		};
	}
}

#endif
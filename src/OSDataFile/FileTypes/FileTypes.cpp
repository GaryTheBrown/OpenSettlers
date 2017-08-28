/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "FileTypes.h"

bool OSData::FileTypes::ToSaveToData(std::vector<char>* data){
	if (data == NULL) return false;

	unsigned short fileTypeNumber = static_cast<short>(this->fileType);
	data->push_back(fileTypeNumber & 0xFF);
	data->push_back((fileTypeNumber >> 8) & 0xFF);

	return true;
}


OSData::FileTypes::eFileType OSData::FileTypes::GetFileType(std::string data){
	if (data == "MenuLayout")
		return eMenuLayout;
	else if (data == "LoadScreen")
		return eLoadingScreenLayout;
	else if(data == "GameOptions")
		return eGameOptions;
	else if(data == "MapSetup")
		return eMapSetup;
	else //Includes Full and Archive
		return eNone;
}

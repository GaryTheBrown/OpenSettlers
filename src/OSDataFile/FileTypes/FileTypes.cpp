/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
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

	data->push_back(static_cast<char>(this->fileType));

	return true;
}

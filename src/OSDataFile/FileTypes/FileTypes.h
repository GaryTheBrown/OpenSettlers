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

namespace OSData{
	class FileTypes {
	public:
		enum eFileType: unsigned char{
			eFull,
			eArchive,
			eMenuLayout,
			eLoadScreen
		};

	protected:
		eFileType fileType;
	public:
		FileTypes(eFileType fileType):fileType(fileType){};
		virtual ~FileTypes(){};


		virtual bool ToSaveToData(std::vector<char>* data);
	};
}

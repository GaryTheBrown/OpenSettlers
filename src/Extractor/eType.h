/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef EXTRACTOR_ETYPE_H_
#define EXTRACTOR_ETYPE_H_


namespace Extractor{
	enum eType{
		FULL,
		//Settlers 2 ONLY
		LBM,
		//Settlers 3 ONLY
		GFX,
		SND,
		MAP
	};
}
#endif

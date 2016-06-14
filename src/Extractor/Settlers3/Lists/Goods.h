/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef SRC_EXTRACTOR_SETTLERS3_LISTS_GOODS_H_
#define SRC_EXTRACTOR_SETTLERS3_LISTS_GOODS_H_

#include <string>

namespace Extractor{
	namespace Settlers3{
		const std::string GoodsList[36] = {	"NOTHING",//0
				"Boards","Stones","Logs","Bread","Coal","Gold Ore","Iron Ore","Fish",
				"Grain","Gold","Iron","Shovel","Hammer","Axe","Pick","Saw",
				"Fishing Rod","Sword","Bow","Spear","Wine","Flour","Pig",
				"Meat","Sulfur","Water","Rice","Gems","Beer","Gun Powder","NOTHING",
				"Scythe",
				//Amazon Only
				"Rice Wine","Mead","Honey"
		};
	}
}



#endif

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS3_LISTS_MAPOBJECTS_H
#define EXTRACTOR_SETTLERS3_LISTS_MAPOBJECTS_H
#include <string>

namespace Extractor{
	namespace Settlers3{
		const std::string MapObjectsList[128] = { "NOTHING",//0
				"Big Stone 1","Big Stone 2","Big Stone 3","Big Stone 4","Big Stone 5","Big Stone 6","Big Stone 7","Big Stone 8",
				"Stone 1","Stone 2","Stone 3","Stone 4",
				"Border Stone 1","Border Stone 2","Border Stone 3","Border Stone 4","Border Stone 5","Border Stone 6","Border Stone 7","Border Stone 8",
				"Small Stone 1","Small Stone 2","Small Stone 3","Small Stone 4","Small Stone 5","Small Stone 6","Small Stone 7","Small Stone 8",
				"Wreck 1","Wreck 2","Wreck 3","Wreck 4","Wreck 5","Grave",
				"Small Plant 1","Small Plant 2","Small Plant 3","Toadstool 1","Toadstool 2","Toadstool 3","Tree Stump 1","Tree Stump 2","Dead Tree 1","Dead Tree 2",
				"Cactus 1","Cactus 2","Cactus 3","Cactus 4","Skeleton",
				"Small Flower 1","Small Flower 2","Small Flower 3","Small Bush 1","Small Bush 2","Small Bush 3","Small Bush 4",
				"Bush 1","Bush 2","Bush 3","Bush 4","Bush 5",
				"Reed 1","Reed 2","Reed 3","Reed 4","Reed 5","Reed 6",
				"Birch 1","Birch 2","Elm 1","Elm 2","Oak",
				//73 - 77
				"UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN",
				"Palm 1","Palm 2",
				//80 - 83
				"UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN",
				"Small Tree",
				//85 - 110
				"UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN",
				"UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN",
				"UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN","UNKNOWN",
				"Very Small Reef","Small Reef","Big Reef","Very Big Reef",
				"Building Stone 1","Building Stone 2","Building Stone 3","Building Stone 4","Building Stone 5","Building Stone 6","Building Stone 7",
				"Building Stone 8","Building Stone 9","Building Stone 10","Building Stone 11","Building Stone 12","Building Stone 13"
		};
	}
}

#endif
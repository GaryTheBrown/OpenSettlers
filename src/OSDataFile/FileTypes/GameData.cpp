/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GameData.h"


OSData::GameAddons OSData::AddonDataFromText(std::string text){
	unsigned char data = 0;

	std::string item;
	std::istringstream buf(text);
	while(std::getline(buf, item, ',')) {
		std::transform(item.begin(), item.end(), item.begin(), toupper);
		if(item == "S2MCD")
			data |= eS2MissionCD;
		else if(item == "S2GOLD")
			data |= eS2Gold;
		else if(item == "S3MCD")
			data |= eS3MissionCD;
		else if(item == "S3AMZ")
			data |= eS3Amazon;
		else if(item == "S3GOLD")
			data |= eS3Gold;
		else if(item == "S4MCD")
			data |= eS4MissionCD;
		else if(item == "S4TRO")
			data |= eS4Trojan;
		else if(item == "S4GOlD")
			data |= eS4Gold;
		else if(item == "S4TNW")
			data |= eS4NewWorld;
		else if(item == "S4COM")
			data |= eS4Community;
	}

	return static_cast<GameAddons>(data);
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/


// http://settlers2.net/documentation/world-map-file-format-wldswd/
#pragma once
#include <string>
#include <vector>

#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/File/Functions.h"
#include "../../../Functions/To.h"
#include "../../../Log.h"

namespace Extractor{
	namespace Settlers2{
		class MAPHeader{
		public:
			struct AreaInfo{
				unsigned char type;//(0:Unused, 1:water, 2:land)
				unsigned short x;
				unsigned short y;
				unsigned int size;
			};
		private:
			std::string name; //20 bytes max
			unsigned short width;
			unsigned short height;
			unsigned char gfxSet;
			unsigned char numPlayers;
			std::string author; //20 bytes max
			unsigned short playerHQx[7];
			unsigned short playerHQy[7];
			unsigned char isInvalid;
			unsigned char playerFaces[7];
			AreaInfo areaInfo[250];

			bool hasExtraWord;

		public:
			explicit MAPHeader(Functions::DataReader* reader);
			~MAPHeader();

			void SaveToFile(std::string location);

			std::string Name(){return this->name;}
			unsigned short Width(){return this->width;}
			unsigned short Height(){return this->height;}
			unsigned char GFXSet(){return this->gfxSet;}
			unsigned char NumPlayers(){return this->numPlayers;}
			std::string Author(){return this->author;}
			unsigned short* PlayerHQx(){return this->playerHQx;}
			unsigned short* PlayerHQy(){return this->playerHQy;}
			unsigned char IsInvalid(){return this->isInvalid;}
			unsigned char* PlayerFaces(){return this->playerFaces;}
			AreaInfo* AreaInfo(){return this->areaInfo;}
			bool HasExtraWord(){return this->hasExtraWord;}
		};
	}
}

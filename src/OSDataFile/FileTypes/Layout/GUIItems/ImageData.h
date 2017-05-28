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
#include <vector>
#include "../../../../Functions/To.h"
#include "../../../../Functions/Image/RGBA.h"
#include "../../../../Functions/Image/RGBImage.h"
#include "../../../../Functions/Image/FileImage.h"
#include "../../../../Functions/File/DataReader.h"

namespace OSData{
	class ImageData{
	public:
		enum ImageLocationType: char{tNone = 0,	tNumber = 1, tColour = 2, tLocation = 3, tData = 4};
	private:
		ImageLocationType type = tNone;
		std::string location = "";
		unsigned int number = 0;
		RGBA colour;
		Functions::RGBImage* image = NULL;
	public:
		ImageData(std::string location):type(tLocation),location(location){};
		ImageData(unsigned int number):type(tNumber),number(number){};
		ImageData(RGBA colour):type(tColour),colour(colour){};
		ImageData(Functions::RGBImage* image):type(tData),image(image){};
		ImageData():type(tNone){};

		void Location(std::string location){this->type = tLocation;this->location = location;}
		void Number(unsigned int number){this->type = tNumber;this->number = number;}
		void Colour(RGBA colour){this->type = tColour;this->colour = colour;}
		void Data(Functions::RGBImage* image){this->type = tData;this->image = image;}
		void None(){this->type = tNone;};

		ImageLocationType Type(){return this->type;}
		std::string Location(){return this->location;}
		unsigned int Number(){return this->number;}
		RGBA Colour(){return this->colour;}
		Functions::RGBImage* Image(){return this->image;};

		void ReadData(Functions::DataReader* reader);
		bool ToSaveToData(std::vector<char>* data);
		bool ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations = NULL);
		bool LinkNumber(std::vector<Functions::RGBImage*>* images);
		std::string ToString();
	};
}

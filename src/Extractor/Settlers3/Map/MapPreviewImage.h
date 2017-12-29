/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef EXTRACTOR_SETTLERS3_MAP_MAPPREVIEWIMAGE_H
#define EXTRACTOR_SETTLERS3_MAP_MAPPREVIEWIMAGE_H
#include <string>
#include "../../../Log.h"
#include "../../../Functions/To.h"
#include "../../../Functions/File/DataReader.h"
#include "../../../Functions/Image/RGBA.h"
#include "../../../Functions/Image/FileImage.h"
#include "MAPParts.h"

namespace Extractor{
	namespace Settlers3{
		class MAPPreviewImage : public MAPParts{
		private:
			//Map Info
			unsigned short length;//Offset(0) height and width the same Length
			unsigned short unknown02; //Offset(2)

			RGBA* imageSquare = NULL;

			unsigned short shearWidth = 0;
			RGBA* imageSheared = NULL;


		public:
			MAPPreviewImage(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey);
			virtual ~MAPPreviewImage();
			virtual std::string HeaderToString();
			void SaveToFile(std::string location);
			void ShearImage();

			const unsigned short Length(){return this->length;};
			const unsigned short Unknown02(){return this->unknown02;};
			RGBA* ImageSquare(){return this->imageSquare;};
			const unsigned short ShearWidth(){return this->shearWidth;};
			RGBA* ImageSheared(){return this->imageSheared;};
		};
	}
}

#endif
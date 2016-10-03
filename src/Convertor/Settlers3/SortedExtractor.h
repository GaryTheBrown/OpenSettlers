//============================================================================
// Name        : SortedExtractor.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS3_SORTEDEXTRACTOR_H_
#define EXTRACTOR_SETTLERS3_SORTEDEXTRACTOR_H_

#include <string>
#include <utility>

#include "../../Log.h"
#include "../../LogSystem/LogSystem.h"
#include "../../Functions/File/Open.h"
#include "../../Functions/File/Functions.h"
#include "../../Functions/File/Run.h"
#include "../../Functions/Image/RGBA.h"
#include "../../Functions/Image/RGBImage.h"
#include "../Extractor.h"
#include "GFXDataType.h"
#include "MAPDataType.h"


namespace Extractor {
	namespace Settlers3{
		class SortedExtractor {
		private:
			unsigned char gameVersion = 0;
			std::string locationofFiles = "";
			std::string locationofSNDFiles = "";
			std::pair <std::string,std::string> SNDFileName;
			std::string locationofGFXFiles = "";
			std::pair <std::string,std::string> GFXFileName;
			std::string locationofMAPFiles = "";
			std::pair <std::string,std::string> MAPFileName;

			const std::string extractionLocation = "Games/TheSettlers3/";
			const std::string extractionLocationGFX = "GFX/";
			const std::string extractionLocationSND = "SND/";
			const std::string extractionLocationLandscape = "Landscape/";
			const std::string extractionLocationGUI = "GUI/";

			void Landscape();
			void GUI(bool extendible);
			void MapObjects(); //missing files are 0 size need to take into account the text file data

		public:
			SortedExtractor(std::string locationofFiles, unsigned char gameVersion);
			virtual ~SortedExtractor(){};
			bool Extract(bool extendible = true);
/*
			enum VersionS3{
				VersionS3CD1 = (1 << 0),
				VersionS3CD2 = (1 << 1),
				VersionS3MCD1 = (1 << 2),
				VersionS3QOTA1 = (1 << 3),
				VersionS3GOLD1 = (1 << 4),
				VersionS3GOLD2 = (1 << 5),
				VersionS3GOG = (1 << 6),
			};*/
		};
	}
}

#endif

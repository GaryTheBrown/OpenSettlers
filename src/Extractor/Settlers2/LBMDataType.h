//============================================================================
// Name        : LBMDataType.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS2_LBMDATATYPE_H_
#define EXTRACTOR_SETTLERS2_LBMDATATYPE_H_

#include <string>

#include "../../LogSystem/LogSystem.h"
#include "../../Log.h"

#include "../../Functions/DataReader.h"
#include "../../Functions/To.h"
#include "../../Functions/File/Functions.h"
#include "../../Functions/File/Save.h"
#include "../../Functions/RGBA.h"


#include "LBM/LBMHeader.h"
#include "LBM/LBMBMHD.h"
#include "LBM/LBMPalette.h"
#include "LBM/LBMAnimationData.h"
#include "LBM/LBMImage.h"

namespace Extractor {
	namespace Settlers2{
		class LBMDataType {
		private:
			LBMHeader* fileHeader = NULL;
			LBMBMHD* pictureHeader = NULL;
			LBMPalette* palette = NULL;
						//DPPS (Deluxe Paint III perspective)
			LBMAnimationData* animationData[16] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; //array of pointers to data
			LBMHeader* previewImage = NULL; //Not really need
			LBMImage* imageData = NULL;

		public:
			LBMDataType(std::string file);
			virtual ~LBMDataType();
		};
	}
}

#endif

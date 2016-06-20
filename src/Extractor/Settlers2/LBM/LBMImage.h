//============================================================================
// Name        : LBMImage.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS2_LBM_LBMIMAGE_H_
#define EXTRACTOR_SETTLERS2_LBM_LBMIMAGE_H_

#include "../../../Functions/DataReader.h"

namespace Extractor{
	namespace Settlers2{
		class LBMImage {
		private:
			unsigned char *image = NULL;
		public:
			LBMImage(Functions::DataReader* reader,unsigned int size);
			virtual ~LBMImage();
		};
	}
}

#endif

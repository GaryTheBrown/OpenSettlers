//============================================================================
// Name        : LBMAnimationData.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS2_LBM_LBMANIMATIONDATA_H_
#define EXTRACTOR_SETTLERS2_LBM_LBMANIMATIONDATA_H_

#include "../../../Functions/DataReader.h"

namespace Extractor{
	namespace Settlers2{
		class LBMAnimationData {
		private:
			unsigned short padding;
			unsigned short rate;
			unsigned short flags;
			unsigned char low;
			unsigned char high;

		public:
			LBMAnimationData(Functions::DataReader* reader);
			virtual ~LBMAnimationData();
		};
	}
}

#endif

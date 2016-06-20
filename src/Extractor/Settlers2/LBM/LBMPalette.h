//============================================================================
// Name        : LBMPalette.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS2_LBM_LBMPALETTE_H_
#define EXTRACTOR_SETTLERS2_LBM_LBMPALETTE_H_

#include "../../../Functions/DataReader.h"
#include "../../../Functions/RGBA.h"

namespace Extractor {
	namespace Settlers2{
		class LBMPalette {
		private:
			RGBA palette[256];

		public:
			LBMPalette(Functions::DataReader* reader);
			virtual ~LBMPalette();

		};
	}
}
#endif /* EXTRACTOR_SETTLERS2_LBM_LBMBMHD_H_ */

//============================================================================
// Name        : LBMHeader.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS2_LBM_LBMHEADER_H_
#define EXTRACTOR_SETTLERS2_LBM_LBMHEADER_H_

#include "../../../Functions/DataReader.h"

namespace Extractor{
	namespace Settlers2{
		class LBMHeader {
		private:
			unsigned int chunkID; //"FORM"  uint 1297239878
			unsigned int lenChunk;//Length of chunk data, in bytes. Does not include the pad byte. Will be the same as the file size minus eight bytes (this field and chunkID are not included in the count)
			unsigned int formatID;//"ILBM"/ "PBM " uint 541934160

		public:
			LBMHeader(Functions::DataReader* reader);
			virtual ~LBMHeader();
		};
	}
}

#endif

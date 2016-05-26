//============================================================================
// Name        : MAPDataType.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS3_MAPDATATYPE_H_
#define EXTRACTOR_SETTLERS3_MAPDATATYPE_H_

#include <string>

#include "../../Log.h"
#include "../../LogSystem/LogSystem.h"

#include "../../Functions/To.h"
#include "../../Functions/FileFunctions.h"
#include "../../Functions/FileSave.h"
#include "../../Functions/DataReader.h"

#include "Map/MAPHeader.h"

namespace Extractor{
	namespace Settlers3{
		class MAPDataType{
		private:
			MAPHeader* header = NULL;

		public:
			MAPDataType(std::string file);
			virtual ~MAPDataType();

			void SaveHeaderData(std::string location);
			void SaveFileData(std::string location);

		};
	}
}
#endif

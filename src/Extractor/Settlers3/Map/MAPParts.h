//============================================================================
// Name        : MAPParts.h
// Author      : Gary_The_Brown
// Description :
//============================================================================

#ifndef EXTRACTOR_SETTLERS3_MAP_MAPPARTS_H_
#define EXTRACTOR_SETTLERS3_MAP_MAPPARTS_H_

#include <string>
#include "../../../Log.h"
#include "../../../LogSystem/LogSystem.h"
#include "../../../Functions/OutputVar.h"
#include "../../../Functions/DataReader.h"
#include "../../../Functions/FileSave.h"

namespace Extractor{
	namespace Settlers3{
		class MAPParts {
		protected:
			unsigned int offset=0;
			unsigned int size=0;
			unsigned int cryptKey=0;
			bool hasBeenDecrypted = false;

			char* data = NULL;

		public:
			MAPParts(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey, bool storeData = false);
			virtual ~MAPParts(){if(this->data != NULL) delete [] this->data;};

			virtual std::string HeaderToString();

			//temp to see info inside file.
			void SaveFileData(std::string location,std::string fileName);

			bool Decrypt(Functions::DataReader* reader);
		};
	}
}
#endif

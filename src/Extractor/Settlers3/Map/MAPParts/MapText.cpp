//============================================================================
// Name        : MAPText.cpp
// Author      : Gary_The_Brown
// Description :
//============================================================================

#include "MapText.h"

namespace Extractor{
	namespace Settlers3{
		MAPText::MAPText(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey):MAPParts(reader,offset,size,cryptKey,false) {

			if(this->hasBeenDecrypted){

				if (this->size == 0){
					LOGSYSTEM->Error("No player information available in Map File!");
					return;
				}

				char nextLetter = reader->ReadChar();
				while (nextLetter != 0x00){
					this->text += nextLetter;
					nextLetter = reader->ReadChar();
				}
			}
			else{
				//decryption failed
				LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
			}
		}

		MAPText::~MAPText() {
		}

		std::string MAPText::ToString(){

			if (this->hasBeenDecrypted == false)
				return MAPParts::HeaderToString();

			return "Text=" + this->text + "\n";
		}
	}
}

//============================================================================
// Name        : MAPParts.cpp
// Author      : Gary_The_Brown
// Description :
//============================================================================

#include "MAPParts.h"

namespace Extractor{
	namespace Settlers3{
		MAPParts::MAPParts(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey, bool storeData){

			this->cryptKey = cryptKey;
			this->hasBeenDecrypted = hasBeenDecrypted;
			this->offset = offset;
			this->size = size;

			if (this->hasBeenDecrypted == false){
				if (this->size > 0){
					this->Decrypt(reader);
					if(this->hasBeenDecrypted == false){
						return;
					}
				}
				else{
					LOGSYSTEM->Error("Failed to Decrypt Size<1" + Functions::ToString(this->offset));
				}
			}
			reader->SetOffset(this->offset);

			if(storeData){
				this->data = new char[this->size];
				for (unsigned int i = 0; i < this->size; i++)
					this->data[i] = reader->ReadChar();
				reader->SetOffset(this->offset);
			}
		}

		std::string MAPParts::HeaderToString(){
			std::string returnString;

			returnString += "Size of Section: " + Functions::ToString(this->size) + "\n";
			returnString += "cryptKey: " + Functions::ToString(this->cryptKey) + "\n";
			returnString += "HasBeenDecrypted: " + (this->hasBeenDecrypted?(std::string)"true":(std::string)"false") + "\n";

			return returnString;

		}

		void MAPParts::SaveFileData(std::string location,std::string fileName){
			if (this->data != NULL)
				Functions::SaveToBinaryFile(location + "/" + fileName,this->data,this->size);
		}

		bool MAPParts::Decrypt(Functions::DataReader* reader){
			if (this->hasBeenDecrypted != false) return true;

			//- key has to be byte
			unsigned char key = this->cryptKey & 0xFF;


			unsigned char* buffer = (unsigned char*)reader->DirectBufferAccess(this->size, this->offset);

			unsigned char byte;
			for (unsigned int i = 0; i < this->size; i++){

				//- read one byte
				byte = *buffer ^ key;

				//- write Byte
				*buffer = byte;

				//Move To Next Byte
				buffer++;

				//- Calculate Next Key
				key = ((key << 1) & 0xFF) ^ byte;
			}

			this->hasBeenDecrypted = true;

			return true;
		}
	}
}
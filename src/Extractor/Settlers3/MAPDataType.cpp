//============================================================================
// Name        : MAPDataType.cpp
// Author      : Gary_The_Brown
// Description :
//============================================================================

#include "MAPDataType.h"
namespace Extractor{
	namespace Settlers3{
		MAPDataType::MAPDataType(std::string file){
			LOGSYSTEM->Log("File:" + file);
			Functions::DataReader* reader = new Functions::DataReader(file);
			reader->SetOffset(0);
			LOGSYSTEM->Log("Reading Header.");
			this->header = new MAPHeader(reader);
			LOGSYSTEM->Log(".OK");

			LOGSYSTEM->Log("Finished Reading Data To Memory.");
		}

		MAPDataType::~MAPDataType(){
			if(this->header != NULL){
				LOGSYSTEM->Log("Deleting Header...");
				delete this->header;
			}
			LOGSYSTEM->Log("Finished Deleting.");
		}

		void MAPDataType::SaveHeaderData(std::string location){

			std::string data;
			if(this->header != NULL){
				data += "**HEADER**\n";
				data += this->header->HeaderToString();
			}
			Functions::SaveToTextFile(location + "/Header.txt",data);
		}

		void MAPDataType::SaveFileData(std::string location){
			if(this->header != NULL){
				LOGSYSTEM->Log("Saving Map Data out to text files...");
				this->header->SaveFileData(location);
			}
		}
	}
}
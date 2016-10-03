/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MAPParts.h"

Extractor::Settlers3::MAPParts::MAPParts(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey, bool storeData)
	:offset(offset),
	 size(size),
	 cryptKey(cryptKey),
	hasBeenDecrypted(false){

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

std::string Extractor::Settlers3::MAPParts::HeaderToString(){
	std::string returnString;

	returnString += "Size of Section: " + Functions::ToString(this->size) + "\n";
	returnString += "cryptKey: " + Functions::ToString(this->cryptKey) + "\n";
	returnString += "HasBeenDecrypted: " + (this->hasBeenDecrypted?(std::string)"true":(std::string)"false") + "\n";

	return returnString;

}

void Extractor::Settlers3::MAPParts::SaveToFile(std::string location,std::string fileName){
	if (this->data != NULL)
		Functions::SaveToBinaryFile(location + "/" + fileName,this->data,this->size);
}

bool Extractor::Settlers3::MAPParts::Decrypt(Functions::DataReader* reader){
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

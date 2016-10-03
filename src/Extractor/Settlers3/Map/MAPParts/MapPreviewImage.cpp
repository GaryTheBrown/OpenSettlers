/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "MapPreviewImage.h"

Extractor::Settlers3::MAPPreviewImage::MAPPreviewImage(Functions::DataReader* reader,unsigned int offset,unsigned int size,unsigned int cryptKey):MAPParts(reader,offset,size,cryptKey,false){

	if(this->hasBeenDecrypted){
		if (this->size == 0){
			LOGSYSTEM->Error("No Preview Image available in mapfile!");
			return;
		}

		//- read image
		this->length = reader->ReadShort();
		this->unknown02 = reader->ReadShort();

		unsigned int dataCount = this->length * this->length;

		if (this->size < dataCount + 4){
			LOGSYSTEM->Error("FilePartSize mismatch with the Preview Image ");
			return;
		}

		//- get buffer for new pixel data
		this->imageSquare = new RGBA[dataCount];

		for (unsigned int i = 0; i< dataCount; i++){
			this->imageSquare[i] = RGBA(reader->ReadShort(),false);
		}

		this->ShearImage();

	}
	else{
		//decryption failed
		LOGSYSTEM->Error("FAIL:Data Not Decrypted!!");
	}
}

Extractor::Settlers3::MAPPreviewImage::~MAPPreviewImage(){
	if (this->imageSquare != NULL)
		delete [] this->imageSquare;
	if (this->imageSheared != NULL)
		delete [] this->imageSheared;
}

std::string Extractor::Settlers3::MAPPreviewImage::HeaderToString(){

	if (this->hasBeenDecrypted == false)
		return MAPParts::HeaderToString();

	std::string returnString;

	returnString += "Image Length=" + Functions::ToString(this->length) + "\n";
	returnString += "Image Sheared Width=" + Functions::ToString(this->shearWidth) + "\n";
	return returnString;
}

void Extractor::Settlers3::MAPPreviewImage::SaveToFile(std::string location){
	Functions::FileImage* fileImage = new Functions::FileImage();
	if (this->imageSquare != NULL)
		fileImage->SaveToRGBImage(location + "/PreviewImageSquare.bmp",this->imageSquare,this->length,this->length);
	if (this->imageSheared != NULL)
		fileImage->SaveToRGBImage(location + "/PreviewImageSheer.bmp",this->imageSheared,this->shearWidth,this->length);
	delete fileImage;
}

void Extractor::Settlers3::MAPPreviewImage::ShearImage(){
	unsigned int shear = this->length/2;
	this->shearWidth = this->length + shear;
	this->imageSheared = new RGBA[this->shearWidth * this->length];

	unsigned int reveseShear = 0;
	unsigned int fromLocation = 0;
	unsigned int toLocation = 0;
	for (unsigned short i = 0; i< this->length/2; i++){
		for (unsigned char j = 0; j < 2; j++){
			toLocation += shear;

			for (unsigned short k = 0; k < this->length; k++){
				this->imageSheared[toLocation] = this->imageSquare[fromLocation];
				toLocation++;
				fromLocation++;
			}
			toLocation += reveseShear;
		}
		shear--;
		reveseShear++;
	}
}

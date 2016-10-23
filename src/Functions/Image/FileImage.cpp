/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "FileImage.h"

Functions::FileImage::FileImage(SaveType saveRGBType,SaveType savePalType)
:saveRGBType(saveRGBType),
 savePalType(savePalType){
}

void Functions::FileImage::SaveToRGBImage(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height){
	switch(this->saveRGBType){
	case Save_Type_BMPv2:
		filename.append(".bmp");
		SaveToRGBBMPv2(filename,imageRGBA,width,height);
		break;
	case Save_Type_BMPv4:
		filename.append(".bmp");
		SaveToRGBBMPv4(filename,imageRGBA,width,height);
		break;
	case Save_Type_PNG:
		filename.append(".png");
		SaveToPNG(filename,imageRGBA,width,height);
		break;
	};
}

void Functions::FileImage::SaveToPaletteImage(std::string filename,unsigned char* image, RGBA* palette, unsigned short width, unsigned short height){
	switch(this->savePalType){
	case Save_Type_BMPv2:
		SaveToPaletteBMPv2(filename,image,palette,width,height);
		break;
	case Save_Type_BMPv4:
		break;
	case Save_Type_PNG:
		break;
	};
}

RGBA* Functions::FileImage::LoadImageToRGBA(std::string filename, unsigned short* width, unsigned short* height){
	RGBA* imageRGBA = NULL;

	if(FileExists(filename)){
		std::string extension = filename.substr(filename.find_last_of(".") + 1);
		std::transform(extension.begin(), extension.end(), extension.begin(), toupper);

		if(extension == "BMP"){
			DataReader* reader = new DataReader(filename);


			//Header Section
			//Read Magic
			std::string magic = reader->ReadString(2);


			//Check File Type Is BMP
			if (magic == "BM"){
				reader->MoveOffset(8);
				int startOffset = reader->ReadInt();
				if (startOffset == 54){
					imageRGBA = LoadBMPv2ToRGBA(reader,width,height);
				}
				else if (startOffset == 122){
					imageRGBA = LoadBMPv4ToRGBA(reader,width,height);
				}
			}
			else{
				//Error and Fail
				LOGSYSTEM->Error("BMP Version NOT Recognised.");
			}
		}else if (extension == "PNG"){
			imageRGBA = LoadPNGToRGBA(filename,width,height);
		}else
			LOGSYSTEM->Error("FILE TYPE NOT Recognised.");
	}else
		LOGSYSTEM->Error("FILE NOT Found.");

	return imageRGBA;
}

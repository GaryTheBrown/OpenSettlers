/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "PlayerColouredBitmap.h"
//TODO Fix errors in this system
Extractor::Settlers2::PlayerColouredBitmap::PlayerColouredBitmap(Functions::DataReader* reader){
	this->xRel = reader->ReadSignedShort();
	this->yRel = reader->ReadSignedShort();
	reader->MoveOffset(4);
	this->width = reader->ReadShort();
	this->height = reader->ReadShort();
	reader->MoveOffset(6);

	unsigned int imageSize = this->height*this->width;
	this->image = new unsigned char[imageSize];
	for (unsigned int i = 0; i < imageSize; i++){
		this->image[i] = 0;
	}
	this->transparency = new bool[imageSize];
	for (unsigned int i = 0; i < imageSize; i++){
		this->transparency[i] = false;
	}

	unsigned int offset = reader->GetOffset();
	std::vector<unsigned int> starts;
	for (unsigned short i = 0; i < this->height; i++){
		starts.push_back(offset + reader->ReadShort());
	}

	for (unsigned int y = 0; y < this->height; y++){
		unsigned short x = 0;

		reader->SetOffset((int)starts[y]);

		while(x < this->width){
			unsigned char code = reader->ReadChar();
			if (code < 0x40){//transparent pixels
				for (unsigned int i = 0; i < code ; i++,x++){
					this->transparency[((y*this->width)+x)] = true;
				}
			} else if (code < 0x80){//uncompressed pixels
				code -= 0x40;
				for (unsigned int i = 0; i < code; i++,x++){
					this->image[((y*this->width)+x)] = reader->ReadChar();
				}
			} else if (code < 0xC0){//player coloured pixels
				if (this->image2 == NULL){
					this->image2 = new unsigned char[imageSize];
					this->transparency2 = new bool[imageSize];
					for (unsigned int i = 0; i < imageSize; i++){
						this->transparency2[i] = true;
					}
				}
				code -= 0x80;
				for (unsigned int i = 0; i < code; i++,x++){
					this->transparency[((y*this->width)+x)] = true;
					this->transparency2[((y*this->width)+x)] = false;
					this->image2[((y*this->width)+x)] = reader->ReadChar();
				}
			} else {//compressed pixels
				code -= 0xC0;
				unsigned char colour = reader->ReadChar();
				for (unsigned int i = 0; i < code; i++,x++){
					this->image[((y*this->width)+x)] = colour;
				}
			}
		}
	}
}
void Extractor::Settlers2::PlayerColouredBitmap::SaveToFile(std::string filename){
	PaletteImage::SaveToFile(filename);

	if (this->image2 != NULL){
		filename.append(".2.bmp");
		Functions::FileImage* fileImage = new Functions::FileImage();
		fileImage->SaveToRGBImage(filename,this->ConvertToRGBA(this->image2,this->transparency2),this->width,this->height);
		//fileImage->SaveToPaletteImage(filename,this->image2,this->palette,this->width,this->height);
		delete fileImage;
	}
}

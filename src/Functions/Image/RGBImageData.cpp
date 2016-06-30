/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "RGBImageData.h"

namespace Functions{

	RGBImageData::RGBImageData(RGBA* imageRGBA, unsigned short height,unsigned short width){
		this->imageRGBA = imageRGBA;
		this->height = height;
		this->width = width;
	}

	RGBImageData::~RGBImageData(){
		if (this->imageRGBA != NULL) delete[] this->imageRGBA;
	}

	void RGBImageData::SaveToRGBBMP(std::string filename){
		filename.append(".bmp");
		Functions::FileImage* fileImage = new Functions::FileImage();
		fileImage->SaveToRGBImage(filename,this->imageRGBA,this->width,this->height);
		delete fileImage;
	}

	RGBA* RGBImageData::CutOutSection(unsigned short X,unsigned short Y,unsigned short height,unsigned short width){
		RGBA* newImage = new RGBA[height*width];

		for(unsigned short i = 0; i < height; i++){
			for(unsigned short j = 0; j < width; j++){
				unsigned int newImageLocation = (i*width)+j;
				unsigned int fromImageLocation = ((X+i)*this->width)+(Y+j);
				newImage[newImageLocation] = this->imageRGBA[fromImageLocation];
			}
		}
		return newImage;
	}

	void RGBImageData::ChangeColour(RGBA from, RGBA to){
		unsigned int size = this->height*this->width;
		for(unsigned int i = 0; i < size; i++){
			if ((this->imageRGBA[i].R == from.R)&&(this->imageRGBA[i].G == from.G)&&(this->imageRGBA[i].B == from.B)&&(this->imageRGBA[i].A == from.A)){
				this->imageRGBA[i].R = to.R;
				this->imageRGBA[i].G = to.G;
				this->imageRGBA[i].B = to.B;
				this->imageRGBA[i].A = to.A;
			}
		}
	}

	void RGBImageData::ChangeColourRange(RGBA from, RGBA to, RGBA range){
		unsigned int size = this->height*this->width;
		for(unsigned int i = 0; i < size; i++){
			if (
					  ((this->imageRGBA[i].R >= (from.R - range.R))&&(this->imageRGBA[i].R <= (from.R + range.R)))
					&&((this->imageRGBA[i].G >= (from.G - range.G))&&(this->imageRGBA[i].G <= (from.G + range.G)))
					&&((this->imageRGBA[i].B >= (from.B - range.B))&&(this->imageRGBA[i].B <= (from.B + range.B)))
					&&((this->imageRGBA[i].A >= (from.A - range.A))&&(this->imageRGBA[i].A <= (from.A + range.A)))
				){
				this->imageRGBA[i].R = to.R;
				this->imageRGBA[i].G = to.G;
				this->imageRGBA[i].B = to.B;
				this->imageRGBA[i].A = to.A;
			}
		}
	}

	void RGBImageData::OverwriteSection(unsigned short X,unsigned short Y,unsigned short height,unsigned short width, RGBA colour){
		for(unsigned short i = 0; i < height; i++){
			for(unsigned short j = 0; j < width; j++){
				unsigned int fromImageLocation = ((X+i)*this->width)+(Y+j);
				this->imageRGBA[fromImageLocation].R = colour.R;
				this->imageRGBA[fromImageLocation].G = colour.G;
				this->imageRGBA[fromImageLocation].B = colour.B;
				this->imageRGBA[fromImageLocation].A = colour.A;
			}
		}
	}
}

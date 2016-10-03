/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "RGBImage.h"

Functions::RGBImage::RGBImage(unsigned short height,unsigned short width)
	:width(width),
	 height(height){
}
Functions::RGBImage::RGBImage(RGBA* imageRGBA, unsigned short height,unsigned short width)
	:width(width),
	 height(height),
	 imageRGBA(imageRGBA){
}

Functions::RGBImage::RGBImage(RGBA* imageRGBA, unsigned short height,unsigned short width,signed short xRel,signed short yRel)
	:width(width),
	 height(height),
	 xRel(xRel),
	 yRel(yRel),
	 imageRGBA(imageRGBA){
}
Functions::RGBImage::~RGBImage(){
	if (this->imageRGBA != NULL)
		delete[] this->imageRGBA;
}

void Functions::RGBImage::SaveToRGBBMP(std::string filename){
	std::string data = "";
	data += "Width=" + Functions::ToString(this->width) + "\n";
	data += "Height=" + Functions::ToString(this->height) + "\n";
	data += "OffsetPositionX=" + Functions::ToString(this->xRel) + "\n";
	data += "OffsetPositionY=" + Functions::ToString(this->yRel);
	Functions::SaveToTextFile(filename + ".txt",data);

	filename.append(".bmp");
	Functions::FileImage* fileImage = new Functions::FileImage();
	fileImage->SaveToRGBImage(filename,this->imageRGBA,this->width,this->height);
	delete fileImage;
}

RGBA* Functions::RGBImage::CutOutSection(unsigned short X,unsigned short Y,unsigned short height,unsigned short width){
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

void Functions::RGBImage::ChangeColour(RGBA from, RGBA to){
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

void Functions::RGBImage::ChangeColourRange(RGBA from, RGBA to, RGBA range){
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

void Functions::RGBImage::OverwriteSection(unsigned short X,unsigned short Y,unsigned short height,unsigned short width, RGBA colour){
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

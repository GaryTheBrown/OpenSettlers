/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "RGBImageData.h"

Extractor::Settlers3::RGBImageData::RGBImageData(Functions::DataReader* reader, unsigned int offset, enumIMGType gfxType,unsigned int colourCode)
	:gfxType(gfxType){

	bool oddOffset = false;
	if (offset % 2 == 1)
		oddOffset = true;

	reader->SetOffset(offset);
	switch(this->gfxType){
	case IMG_GFX_Landscape:
		this->width = reader->ReadShort();
		this->height = reader->ReadShort();
		reader->ReadShort(); //Space
		break;
	case IMG_GFX_Object:
	case IMG_GFX_Shadow:
		reader->ReadInt(); //Magic
		//no break
	case IMG_GFX_Gui:
		this->width = reader->ReadShort();
		this->height = reader->ReadShort();
		this->xRel = reader->ReadSignedShort();
		this->yRel = reader->ReadSignedShort();
		if(oddOffset == false){
			reader->ReadShort(); //Space
		}
		else{
			reader->ReadChar(); //Space
		}
		break;
	default:
		break;
	}

	if (this->height > 0 && this->width > 0){
		this->imageRGBA = new RGBA[this->height*this->width];
		unsigned int pixelLocation = 0;
		int x = 0; //- Shadow Bogus Pixel Count Protection
		for (unsigned short pixelH = 0; pixelH < this->height;){
			unsigned char pixelCount = reader->ReadChar();
			unsigned char pixelJump = reader->ReadChar();

			//- 1-7bits indicate the count of transparency/black - bit 8 indicates the end of line
			pixelLocation +=(pixelJump & 0x7F);
			//Read Block Of Data
			//unsigned short pixel;
			if (pixelCount <= width - x){
				for (unsigned char i = 0; i < pixelCount; i++){

					//shadow
					if(gfxType == IMG_GFX_Shadow){
						this->imageRGBA[pixelLocation].B = this->imageRGBA[pixelLocation].G = this->imageRGBA[pixelLocation].R = 0;
						this->imageRGBA[pixelLocation].A = 127;
					}
					// Others
					else
						this->imageRGBA[pixelLocation] = RGBA(reader->ReadShort(),((colourCode == 0xf800)?true:false));

					pixelLocation++;
					x++;
				}
			}
			//- end of line detection (8th bit of PixelJump)
			if ((pixelJump & 0x80) > 0){
				pixelH++;
				pixelLocation = pixelH*this->width; //- jump to Line start
				x = 0;
			}
		}
	}
}
Extractor::Settlers3::RGBImageData::RGBImageData(RGBA* imageRGBA, enumIMGType gfxType, unsigned short width, unsigned short height, signed short xRel, signed short yRel)
	:Functions::RGBImage(imageRGBA,width,height,xRel,yRel),
	gfxType(gfxType){
}
Extractor::Settlers3::RGBImageData::RGBImageData(RGBA* imageRGBA, unsigned short width,unsigned short height,signed short xRel,signed short yRel)
	:Functions::RGBImage(imageRGBA,width,height,xRel,yRel),
	gfxType(IMG_GFX_none){
}

void Extractor::Settlers3::RGBImageData::SaveToFile(std::string filename){
	if ((this->gfxType != IMG_GFX_Landscape)&&(this->xRel !=0 || this->yRel != 0)){
		std::string data;
		data += "Height=" + Functions::ToString(this->height) + "\n";
		data += "Width=" + Functions::ToString(this->width) + "\n";
		data += "OffsetPositionX=" + Functions::ToString(this->xRel) + "\n";
		data += "OffsetPositionY=" + Functions::ToString(this->yRel) + "\n";
		Functions::SaveToTextFile((filename  + ".txt"),data);
	}
	if (this->height > 0 && this->width > 0)
		RGBImage::SaveToFile(filename);
}

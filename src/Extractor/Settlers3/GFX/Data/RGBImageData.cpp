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

namespace Extractor{
	namespace Settlers3{

		RGBImageData::RGBImageData(Functions::DataReader* reader, unsigned int offset, enumIMGType gfxType,unsigned int colourCode){

			this->gfxType = gfxType;

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
		RGBImageData::RGBImageData(RGBA* imageRGBA, enumIMGType gfxType, unsigned short height, unsigned short width, signed short xRel, signed short yRel){
			this->imageRGBA = imageRGBA;
			this->height = height;
			this->width = width;
			this->xRel = xRel;
			this->yRel = yRel;
			this->gfxType = gfxType;
		}
		RGBImageData::RGBImageData(RGBA* imageRGBA, unsigned short height,unsigned short width,signed short xRel,signed short yRel){
			this->imageRGBA = imageRGBA;
			this->height = height;
			this->width = width;
			this->xRel = xRel;
			this->yRel = yRel;
			this->gfxType = IMG_GFX_none;
		}

		RGBImageData::~RGBImageData(){
			if (this->imageRGBA != NULL) delete[] this->imageRGBA;
		}

		void RGBImageData::SaveToFile(std::string filename){
			if ((this->gfxType != IMG_GFX_Landscape)&&(this->xRel !=0 || this->yRel != 0)){
				std::string data;
				data += "Height=" + Functions::ToString(this->height) + "\n";
				data += "Width=" + Functions::ToString(this->width) + "\n";
				data += "OffsetPositionX=" + Functions::ToString(this->xRel) + "\n";
				data += "OffsetPositionY=" + Functions::ToString(this->yRel) + "\n";
				Functions::SaveToTextFile((filename  + ".txt"),data);
			}

			if (this->height > 0 && this->width > 0)
				this->SaveToRGBBMP(filename);
		}

		void RGBImageData::SaveToRGBBMP(std::string filename){
			filename.append(".bmp");
			Functions::FileImage* fileImage = new Functions::FileImage();
			fileImage->SaveToRGBImage(filename,this->imageRGBA,this->width,this->height,this->xRel,this->yRel);
			delete fileImage;
		}

		RGBImageData* RGBImageData::CutOutSection(unsigned short X,unsigned short Y,unsigned short height,unsigned short width){
			RGBA* newImage = new RGBA[height*width];

			for(unsigned short i = 0; i < height; i++){
				for(unsigned short j = 0; j < width; j++){
					unsigned int newImageLocation = (i*width)+j;
					unsigned int fromImageLocation = ((X+i)*this->width)+(Y+j);
					newImage[newImageLocation] = this->imageRGBA[fromImageLocation];
				}
			}
			return new RGBImageData(newImage,height,width,0,0);
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
}

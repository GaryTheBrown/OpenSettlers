/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "PaletteImageData.h"
namespace Extractor{
	namespace Settlers3{

		PaletteImageData::PaletteImageData(Functions::DataReader* reader, unsigned int offset, RGBA* Palette){
			reader->SetOffset(offset);
			reader->ReadInt(); //Magic
			this->width = reader->ReadShort();
			this->height = reader->ReadShort();
			this->xRel = reader->ReadSignedShort();
			this->yRel = reader->ReadSignedShort();
			reader->ReadShort(); //Space

			this->image = new unsigned char[this->height*this->width];

			//temp transparency solution
			this->transparency = new bool[this->height*this->width];

			for (int i = 0; i < (this->height*this->width);i++){
				this->image[i] = 0;
				this->transparency[i] = true;
			}

			int pixelLocation = 0;
			for (int pixelH = 0; pixelH < this->height;){
				int pixelCount = reader->ReadChar();
				int pixelJump = reader->ReadChar();//40 = 0

				//- 1-7bits indicate the count of transparency/black - bit 8 indicates the end of line
				pixelLocation +=(pixelJump & 0x7F);

				//Read Block Of Data
				for (int i = 0; i < pixelCount; i++){

					//Read Pixel
					this->image[pixelLocation] = reader->ReadChar();
					//For if we use transparency on palette[0] comment out above!!
					//unsigned char pixel = reader->ReadChar();
					//if(pixel == 0) pixel = 1;
					//this->imagePalette[pixelLocation] = pixel;

					//temp transparency workaround
					this->transparency[pixelLocation] = false;
					pixelLocation++;
				}
				//- end of line detection (8th bit of PixelJump)
				if ((pixelJump & 0x80) > 0){
					pixelH++;
					pixelLocation = pixelH*this->width; //- jump to Line start
				}
			}

			if (Palette != NULL){
				this->SetPalette(Palette);
			}
		}

		PaletteImageData::~PaletteImageData(){
			delete[] this->image;
		}

		void PaletteImageData::SaveToFile(std::string filename){

			std::string data = "";
			data += "Width			=" + Functions::ToString(this->width) + "\n";
			data += "Height			=" + Functions::ToString(this->height) + "\n";
			data += "OffsetPositionX=" + Functions::ToString(this->xRel) + "\n";
			data += "OffsetPositionY=" + Functions::ToString(this->yRel) + "\n";

			//add the data
			data += "Image=" + Functions::ToString(this->width) + "x" + Functions::ToString(this->height) + "\n";
			for(int i = 0; i < this->height; i++){
				for(int j = 0; j < this->width; j++){
					int pixel = (i*this->width)+j;
					if (this->transparency[pixel])
						data += "XXX,";
					else if (this->image[pixel] > 99)
						data += Functions::ToString((int)this->image[pixel]) + ",";
					else if(this->image[pixel] > 9)
						data += "0" + Functions::ToString((int)this->image[pixel]) + ",";
					else
						data += "00" + Functions::ToString((int)this->image[pixel]) + ",";
				}
				data += "\n";
			}

			Functions::SaveToTextFile(filename + ".txt",data);

			//show Data As RGB Files
			if(paletteCheck){
				RGBImageData* imageRGB = this->ConvertToRGBA();
				imageRGB->SaveToRGBBMP(filename);
			}
			else{ //This Function is Working but preview is wrong for the file.
				filename.append(".bmp");
				Functions::FileImage* fileImage = new Functions::FileImage();
				fileImage->SaveToPaletteImage(filename,this->image,this->palette,this->width,this->height);
				delete fileImage;
			}
		}

		void PaletteImageData::SetPalette(RGBA* Palette){
			for (signed short i = 0; i < 256; i++){//BGR order
				this->palette[(i*4)] = Palette[i].B;
				this->palette[(i*4)+1] = Palette[i].G;
				this->palette[(i*4)+2] = Palette[i].R;
				this->palette[(i*4)+3] = Palette[i].A;
			}
		}

		RGBImageData* PaletteImageData::ConvertToRGBA(){
			RGBA *imageRGBA = new RGBA[this->height*this->width];

			for (int i = 0; i < (this->height*this->width);i++){
				if(this->transparency[i] == true){
					imageRGBA[i].A = 0;
					imageRGBA[i].R = 0;
					imageRGBA[i].G = 0;
					imageRGBA[i].B = 0;
				}
				else{
					imageRGBA[i].B = this->palette[(((this->image[i])*4)+0)];
					imageRGBA[i].G = this->palette[(((this->image[i])*4)+1)];
					imageRGBA[i].R = this->palette[(((this->image[i])*4)+2)];
					imageRGBA[i].A = this->palette[(((this->image[i])*4)+3)];
				}
			}
			return new RGBImageData(imageRGBA,RGBImageData::IMG_GFX_Torso, this->height,this->width,this->xRel,this->yRel);
		}
	}
}

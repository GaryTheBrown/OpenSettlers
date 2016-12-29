/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "../FileImage.h"

void Functions::FileImage::SaveToRGBBMPv2(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height){
	// mimeType = "image/bmp";
	unsigned char file[14] = {
			'B','M', // magic
			0,0,0,0, // size in bytes
			0,0, // app data
			0,0, // app data
			54,0,0,0 // start of data offset
	};

	unsigned char info[40] = {
			0x28,0x00,0x00,0x00,	//40 bytes	Number of bytes in the DIB header (from this point)
			0x00,0x00,0x00,0x00,	//4 pixels (left to right order)	Width of the bitmap in pixels
			0x00,0x00,0x00,0x00,	//2 pixels (bottom to top order)	Height of the bitmap in pixels
			0x01,0x00,				//1 plane	Number of colour planes being used
			0x20,0x00,				//Number of bits per pixel
			0x00,0x00,0x00,0x00,	//compression
			0x00,0x00,0x00,0x00,	//Size of the raw bitmap data (including padding)
			0x00,0x00,0x00,0x00,	//preferred resolution in pixels per meter
			0x00,0x00,0x00,0x00,	//preferred resolution in pixels per meter
			0x00,0x00,0x00,0x00,	//0 colours	Number of colours in the palette
			0x00,0x00,0x00,0x00		//0 important colours	0 means all colours are important
	};

	int sizeData = width*height*4;
	int sizeAll  = sizeData + sizeof(file) + sizeof(info);

	file[2] = (unsigned char)(sizeAll) & 0xFF;
	file[3] = (unsigned char)(sizeAll>> 8) & 0xFF;
	file[4] = (unsigned char)(sizeAll>>16) & 0xFF;
	file[5] = (unsigned char)(sizeAll>>24) & 0xFF;

	info[4] = (unsigned char)(width) & 0xFF;
	info[5] = (unsigned char)(width>> 8) & 0xFF;
	info[6] = (unsigned char)(width>>16) & 0xFF;
	info[7] = (unsigned char)(width>>24) & 0xFF;

	info[8] = (unsigned char)(height) & 0xFF;
	info[9] = (unsigned char)(height>> 8) & 0xFF;
	info[10] = (unsigned char)(height>>16) & 0xFF;
	info[11] = (unsigned char)(height>>24) & 0xFF;

	//Check File Doesn't Exist if it does delete it
	if(FileExists(filename))
		remove(filename.c_str());

	std::ofstream ofile;
	//open the ofile
	ofile.open(filename.c_str(),std::ios::binary);

	//Write Header Info To File
	ofile.write((char*)file, sizeof(file));
	ofile.write((char*)info, sizeof(info));

	//Write Pixel Data To File (bottom to top)
	int pixel = 0;
	for (unsigned short y=height; y>0; y-- ){
		for (unsigned short x=0; x<width; x++ ){
			pixel = ((y - 1) * width) + x;

			unsigned char outPixel[4];
			outPixel[0] = imageRGBA[pixel].B; //Red
			outPixel[1] = imageRGBA[pixel].G; //Green
			outPixel[2] = imageRGBA[pixel].R; //Blue
			outPixel[3] = imageRGBA[pixel].A; //Alpha

			ofile.write((char*)outPixel,4);
		}
	}

	//Close The File
	ofile.close();
}

void Functions::FileImage::SaveToPaletteBMPv2(std::string filename,unsigned char* image, RGBA* palette, unsigned short width, unsigned short height){
	// mimeType = "image/bmp";
	char file[14] = {
			'B','M', // magic
			0x00,0x00,0x00,0x00, // size in bytes
			0x00,0x00, // app data
			0x00,0x00, // app data
			0x36,0x04,0,0 // start of data offset
	};

	char info[40] = {
			0x28,0x00,0x00,0x00,	//40 bytes	Number of bytes in the DIB header (from this point)
			0x00,0x00,0x00,0x00,	//4 pixels (left to right order)	Width of the bitmap in pixels
			0x00,0x00,0x00,0x00,	//2 pixels (bottom to top order)	Height of the bitmap in pixels
			0x01,0x00,				//1 plane	Number of colour planes being used
			0x08,0x00,				//Number of bits per pixel
			0x00,0x00,0x00,0x00,	//compression
			0x00,0x00,0x00,0x00,	//Size of the raw bitmap data (including padding)
			0x00,0x00,0x00,0x00,	//preferred resolution in pixels per meter
			0x00,0x00,0x00,0x00,	//preferred resolution in pixels per meter
			0x00,0x00,0x00,0x00,	//0 colours	Number of colours in the palette
			0x00,0x00,0x00,0x00,	//0 important colours	0 means all colours are important
	};

	char charPalette[1024]; // BGRA Format
	if (palette != NULL){
		for (signed short i = 0; i < 256; i++){//BGR order
			charPalette[(i*4)] = palette[i].B;
			charPalette[(i*4)+1] = palette[i].G;
			charPalette[(i*4)+2] = palette[i].R;
			charPalette[(i*4)+3] = palette[i].A;
		}
	}

	//check if padding needed
	int paddingCount = 0; // Set pad byte count per row to zero by default.
	// Each row needs to be a multiple of 4 bytes.
	if (width % 4 != 0) paddingCount = 4 - (width % 4);

	char padding[3] = {0,0,0};
	int sizeData = width*height + (paddingCount*height);
	int sizeAll  = sizeData + sizeof(file) + sizeof(info);

	file[2] = (char)(sizeAll) & 0xFF;
	file[3] = (char)(sizeAll>> 8) & 0xFF;
	file[4] = (char)(sizeAll>>16) & 0xFF;
	file[5] = (char)(sizeAll>>24) & 0xFF;

	info[4] = (char)(width) & 0xFF;
	info[5] = (char)(width>> 8) & 0xFF;
	info[6] = (char)(width>>16) & 0xFF;
	info[7] = (char)(width>>24) & 0xFF;

	info[8] = (char)(height) & 0xFF;
	info[9] = (char)(height>> 8) & 0xFF;
	info[10] = (char)(height>>16) & 0xFF;
	info[11] = (char)(height>>24) & 0xFF;

	//Check File Doesn't Exist if it does delete it
	if(FileExists(filename))
		remove(filename.c_str());

	std::ofstream ofile;
	//open the ofile
	ofile.open(filename.c_str(),std::ios::binary);
	//Write Header To File (bottom to top)
	ofile.write((char*)file, sizeof(file));
	ofile.write((char*)info, sizeof(info));

	//Add in show Palette [0][0]
	ofile.write((char*)charPalette, 1024);

	//Write Pixel Data To File
	int pixel = 0;
	for ( int y=height; y>0; y-- ){
		pixel = (y - 1) * width;
		ofile.write((char*)image+pixel,width);
		//padding to 4
		if(paddingCount > 0)
			ofile.write((char*)padding,paddingCount);
	}

	//Close The File
	ofile.close();
}

RGBA* Functions::FileImage::LoadBMPv2ToRGBA(DataReader* reader, unsigned short* width, unsigned short* height, unsigned int dataOffset){

	*width = reader->ReadInt();
	*height = reader->ReadInt();
	reader->MoveOffset(2);
	int bitsPerPixel = reader->ReadShort();
	reader->MoveOffset(24);

	char padding = ((bitsPerPixel/8) * (*width))%4;

	RGBA* imageRGBA = new RGBA[(*height)*(*width)];

	RGBA palette[256];

	if (bitsPerPixel == 8){
		//Read Palette
		for (int i = 0; i < 256; i++){
			palette[i].B = reader->ReadChar();
			palette[i].G = reader->ReadChar();
			palette[i].R = reader->ReadChar();
			palette[i].A = 255;
			reader->ReadChar();
		}
	}
	reader->SetOffset(dataOffset);

	int pixel = 0;
	for (unsigned short y=(*height); y>0; y-- ){
		for (unsigned short x=0; x<(*width); x++ ){
			pixel = ((y - 1) * (*width)) + x;

			if (bitsPerPixel == 8){
				unsigned char singlePixel = reader->ReadChar();
				imageRGBA[pixel].B = palette[singlePixel].B;
				imageRGBA[pixel].G = palette[singlePixel].G;
				imageRGBA[pixel].R = palette[singlePixel].R;
				imageRGBA[pixel].A = palette[singlePixel].A;
			}
			if (bitsPerPixel == 24){
				imageRGBA[pixel].B = reader->ReadChar();
				imageRGBA[pixel].G = reader->ReadChar();
				imageRGBA[pixel].R = reader->ReadChar();
				imageRGBA[pixel].A = 255;
			}
			if (bitsPerPixel == 32){
				imageRGBA[pixel].B = reader->ReadChar();
				imageRGBA[pixel].G = reader->ReadChar();
				imageRGBA[pixel].R = reader->ReadChar();
				imageRGBA[pixel].A = reader->ReadChar();
			}
			//check padding and skip it.
			for (char i=0; i<padding; i++)
				reader->ReadChar();
		}
	}

	reader->~DataReader();
	return imageRGBA;
}

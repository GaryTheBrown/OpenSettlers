/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "Image.h"

namespace Functions{
	FileImage::FileImage(SaveType saveRGBType,SaveType savePalType){
		this->saveRGBType = saveRGBType;
		this->savePalType = savePalType;
	}

	void FileImage::SaveToRGBImage(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height,signed short xRel, signed short yRel){
		switch(this->saveRGBType){
		case Save_Type_BMPv2:
				SaveToRGBBMPv2(filename,imageRGBA,width,height,xRel,yRel);
				break;
		case Save_Type_BMPv4:
				SaveToRGBBMPv4(filename,imageRGBA,width,height,xRel,yRel);
				break;
		};
	}

	void FileImage::SaveToPaletteImage(std::string filename,unsigned char* image, unsigned char* palette, unsigned short width, unsigned short height){
		switch(this->savePalType){
			case Save_Type_BMPv2:
				SaveToPaletteBMPv2(filename,image,palette,width,height);
				break;
			case Save_Type_BMPv4:
				break;
		};
	}

	RGBA* FileImage::LoadImageToRGBA(std::string filename, unsigned short* width, unsigned short* height,signed short* xRel, signed short* yRel){

		DataReader* reader = new DataReader(filename);
		RGBA* imageRGBA = NULL;

		//Header Section
		//Read Magic
		char magic1 = reader->ReadChar();
		char magic2 = reader->ReadChar();

		//Check File Type Is BMP
		if (magic1 == 'B' || magic2 == 'M'){
			//Read Rest Of header
			/*int fileSize =*/ reader->ReadInt();
			*xRel = reader->ReadSignedShort();
			*yRel = reader->ReadSignedShort();
			int startOffset = reader->ReadInt();
			if (startOffset == 54){
				imageRGBA = LoadBMPv2ToRGBA(reader,width,height);
			}
			else if (startOffset == 122){
				//imageRGBA = LoadBMPv4ToRGBA(reader,width,height);
				LOGSYSTEM->Error("BMPv4 Loading NOT IMPLEMENTED YET");
			}
		}
		else{
			//Error and Fail
			LOGSYSTEM->Error("FILE TYPE NOT Recognised.");
			return NULL;
		}



		return imageRGBA;
	}

	void FileImage::SaveToRGBBMPv2(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height,signed short xRel, signed short yRel){
		// mimeType = "image/bmp";
		unsigned char file[14] = {
				'B','M', // magic
				0,0,0,0, // size in bytes
				0,0, // app data xRel for us
				0,0, // app data yRel for us
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

		file[6] = (unsigned char)(xRel) & 0xFF;
		file[7] = (unsigned char)(xRel>> 8) & 0xFF;

		file[8] = (unsigned char)(yRel) & 0xFF;
		file[9] = (unsigned char)(yRel>> 8) & 0xFF;


		info[4] = (unsigned char)(width) & 0xFF;
		info[5] = (unsigned char)(width>> 8) & 0xFF;
		info[6] = (unsigned char)(width>>16) & 0xFF;
		info[7] = (unsigned char)(width>>24) & 0xFF;

		info[8] = (unsigned char)(height) & 0xFF;
		info[9] = (unsigned char)(height>> 8) & 0xFF;
		info[10] = (unsigned char)(height>>16) & 0xFF;
		info[11] = (unsigned char)(height>>24) & 0xFF;

		//Check File Doesn't Exist if it does delete it
		std::ifstream infile(filename.c_str());
		if(infile.good())
			remove(filename.c_str());
		infile.close();

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

	void FileImage::SaveToRGBBMPv4(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height,signed short xRel, signed short yRel){
		// mimeType = "image/bmp";
		unsigned char file[14] = {
				'B','M', // magic
				0,0,0,0, // size in bytes
				0,0, // app data xRel for us
				0,0, // app data yRel for us
				122,0,0,0 // start of data offset
		};

		unsigned char info[108] = {
				0x6C,0x00,0x00,0x00,	//108 bytes	Number of bytes in the DIB header (from this point)
				0x00,0x00,0x00,0x00,	//4 pixels (left to right order)	Width of the bitmap in pixels
				0x00,0x00,0x00,0x00,	//2 pixels (bottom to top order)	Height of the bitmap in pixels
				0x01,0x00,				//1 plane	Number of color planes being used
				0x20,0x00,				//32 bits	Number of bits per pixel
				0x03,0x00,0x00,0x00,	//3 Compression used (BI_BITFIELDS)
				0x00,0x00,0x00,0x00,	//0	Size of the raw bitmap data (including padding)
				0x00,0x00,0x00,0x00,	//2835 pixels/meter horizontal	Print resolution of the image,72 DPI × 39.3701 inches per meter yields 2834.6472
				0x00,0x00,0x00,0x00,	//2835 pixels/meter vertical
				0x00,0x00,0x00,0x00,	//0 colors	Number of colors in the palette
				0x00,0x00,0x00,0x00,	//0 important colors	0 means all colors are important

				0x00,0x00,0xFF,0x00,	//00FF0000 in big-endian	Red channel bit mask (valid because BI_BITFIELDS is specified)
				0x00,0xFF,0x00,0x00,	//0000FF00 in big-endian	Green channel bit mask (valid because BI_BITFIELDS is specified)
				0xFF,0x00,0x00,0x00,	//000000FF in big-endian	Blue channel bit mask (valid because BI_BITFIELDS is specified)
				0x00,0x00,0x00,0xFF,	//FF000000 in big-endian	Alpha channel bit mask

				0x00,0x00,0x00,0x00,	// COLOR SPACE
				0x00,0x00,0x00,0x00,	// X coordinate of red endpoint
				0x00,0x00,0x00,0x00,	// Y coordinate of red endpoint
				0x00,0x00,0x00,0x00,	// Z coordinate of red endpoint
				0x00,0x00,0x00,0x00,	// X coordinate of green endpoint
				0x00,0x00,0x00,0x00,	// Y coordinate of green endpoint
				0x00,0x00,0x00,0x00,	// Z coordinate of green endpoint
				0x00,0x00,0x00,0x00,	// X coordinate of blue endpoint
				0x00,0x00,0x00,0x00,	// Y coordinate of blue endpoint
				0x00,0x00,0x00,0x00,	// Z coordinate of blue endpoint
				0x00,0x00,0x00,0x00,	// Gamma red coordinate scale value
				0x00,0x00,0x00,0x00,	// Gamma green coordinate scale value
				0x00,0x00,0x00,0x00		// Gamma blue coordinate scale value
		};

		int sizeData = width*height*4;
		int sizeAll  = sizeData + sizeof(file) + sizeof(info);

		file[2] = (unsigned char)(sizeAll) & 0xFF;
		file[3] = (unsigned char)(sizeAll>> 8) & 0xFF;
		file[4] = (unsigned char)(sizeAll>>16) & 0xFF;
		file[5] = (unsigned char)(sizeAll>>24) & 0xFF;

		file[6] = (unsigned char)(xRel) & 0xFF;
		file[7] = (unsigned char)(xRel>> 8) & 0xFF;

		file[8] = (unsigned char)(yRel) & 0xFF;
		file[9] = (unsigned char)(yRel>> 8) & 0xFF;


		info[4] = (unsigned char)(width) & 0xFF;
		info[5] = (unsigned char)(width>> 8) & 0xFF;
		info[6] = (unsigned char)(width>>16) & 0xFF;
		info[7] = (unsigned char)(width>>24) & 0xFF;

		info[8] = (unsigned char)(height) & 0xFF;
		info[9] = (unsigned char)(height>> 8) & 0xFF;
		info[10] = (unsigned char)(height>>16) & 0xFF;
		info[11] = (unsigned char)(height>>24) & 0xFF;

		//Check File Doesn't Exist if it does delete it
		std::ifstream infile(filename.c_str());
		if(infile.good())
			remove(filename.c_str());
		infile.close();

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

	void FileImage::SaveToPaletteBMPv2(std::string filename,unsigned char* image, unsigned char* palette, unsigned short width, unsigned short height){
		// mimeType = "image/bmp";
		unsigned char file[14] = {
				'B','M', // magic
				0x00,0x00,0x00,0x00, // size in bytes
				0x00,0x00, // app data
				0x00,0x00, // app data
				0x36,0x04,0,0 // start of data offset
		};

		unsigned char info[40] = {
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

		//check if padding needed
		int paddingCount = 0; // Set pad byte count per row to zero by default.
		// Each row needs to be a multiple of 4 bytes.
		if (width % 4 != 0) paddingCount = 4 - (width % 4);

		char padding[3] = {0,0,0};
		int sizeData = width*height + (paddingCount*height);
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
		std::ifstream infile(filename.c_str());
		if(infile.good())
			remove(filename.c_str());

		infile.close();
		std::ofstream ofile;

		//open the ofile
		ofile.open(filename.c_str(),std::ios::binary);
		//Write Header To File (bottom to top)
		ofile.write((char*)file, sizeof(file));
		ofile.write((char*)info, sizeof(info));

		//Add in show Palette [0][0]
		ofile.write((char*)palette, 1024);

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

	RGBA* FileImage::LoadBMPv2ToRGBA(DataReader* reader, unsigned short* width, unsigned short* height){

		//INFO Section
		/*int infoSize =*/ reader->ReadInt();

		*width = reader->ReadInt();
		*height = reader->ReadInt();
		/*int colourPlane =*/ reader->ReadShort();
		int bitsPerPixel = reader->ReadShort();
		/*int compressionType =*/ reader->ReadInt();
		/*int sizeImageData =*/ reader->ReadInt();
		/*int horizontalResolution =*/ reader->ReadInt();
		/*int verticalResolution =*/ reader->ReadInt();
		/*int numberColours =*/ reader->ReadInt();
		/*int importantColours =*/ reader->ReadInt();

		char padding = ((bitsPerPixel/8) * (*width))%4;

		RGBA* imageRGBA = new RGBA[(*height)*(*width)];

		RGBA palette[256];

		if (bitsPerPixel == 8){
			//Read Palette
			for (int i = 0; i < 256; i++){
				palette[i].B = reader->ReadChar();
				palette[i].G = reader->ReadChar();
				palette[i].R = reader->ReadChar();
				palette[i].A = reader->ReadChar();
			}
		}

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
}

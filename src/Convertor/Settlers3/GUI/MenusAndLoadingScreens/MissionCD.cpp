/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "../ConvertGUI.h"

void Converter::Settlers3::ConvertGUI::MissionCD(){
/*
//Mission CD
		if(extendible){
			//Main Colour (58,178,13)
			unsigned short width, height;
			signed short xRel, yRel;
			Functions::FileImage* fileImage = new Functions::FileImage();
			RGBA* imageRGBA = fileImage->LoadImageToRGBA(this->locationofFiles + "s3mcd/install/english/missionm.bmp", &width, &height);
			delete fileImage;
			RGBImageData* image = new RGBImageData(imageRGBA,height,width,xRel,yRel);
			RGBA from,to,range;

			//Middle Bar
			image->CutOutSection(0,386,258,1)->SaveToFile(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_MiddleBar");

			//Clean Up Green
			range = {64,50,64,0};
			from = {64,205,64,255};
			image->ChangeColourRange(from,to,range);

			range = {10,10,10,0};
			from = {9,57,0,255};
			image->ChangeColourRange(from,to,range);
			from = {29,90,10,255};
			image->ChangeColourRange(from,to,range);
			from = {39,129,8,255};
			image->ChangeColourRange(from,to,range);
			from = {44,142,14,255};
			image->ChangeColourRange(from,to,range);
			from = {49,172,2,255};
			image->ChangeColourRange(from,to,range);
			from = {73,219,28,255};
			image->ChangeColourRange(from,to,range);
			from = {98,204,62,255};
			image->ChangeColourRange(from,to,range);
			from = {103,217,68,255};
			image->ChangeColourRange(from,to,range);
			from = {129,218,102,255};
			image->ChangeColourRange(from,to,range);
			from = {152,239,125,255};
			image->ChangeColourRange(from,to,range);
			from = {153,242,126,255};
			image->ChangeColourRange(from,to,range);
			from = {10,61,0,255};
			image->ChangeColourRange(from,to,range);
			from = {39,130,8,255};
			image->ChangeColourRange(from,to,range);
			from = {61,187,14,255};
			image->ChangeColourRange(from,to,range);
			from = {46,146,10,255};
			image->ChangeColourRange(from,to,range);
			from = {62,188,14,255};
			image->ChangeColourRange(from,to,range);
			from = {61,186,14,255};
			image->ChangeColourRange(from,to,range);
			from = {60,185,14,255};
			image->ChangeColourRange(from,to,range);
			from = {60,184,14,255};
			image->ChangeColourRange(from,to,range);
			from = {60,183,13,255};
			image->ChangeColourRange(from,to,range);
			from = {59,182,13,255};
			image->ChangeColourRange(from,to,range);
			from = {60,182,13,255};
			image->ChangeColourRange(from,to,range);
			from = {61,185,14,255};
			image->ChangeColourRange(from,to,range);
			from = {61,188,14,255};
			image->ChangeColourRange(from,to,range);
			from = {40,131,8,255};
			image->ChangeColourRange(from,to,range);
			from = {11,63,0,255};
			image->ChangeColourRange(from,to,range);
			from = {29,91,10,255};
			image->ChangeColourRange(from,to,range);
			from = {128,218,101,255};
			image->ChangeColourRange(from,to,range);
			from = {45,144,9,255};
			image->ChangeColourRange(from,to,range);
			from = {68,205,25,255};
			image->ChangeColourRange(from,to,range);
			from = {17,77,2,255};
			image->ChangeColourRange(from,to,range);
			from = {33,103,10,255};
			image->ChangeColourRange(from,to,range);
			from = {158,255,125,255};
			image->ChangeColourRange(from,to,range);
			from = {140,220,106,255};
			image->ChangeColourRange(from,to,range);
			from = {133,235,99,255};
			image->ChangeColourRange(from,to,range);
			from = {67,145,38,255};
			image->ChangeColourRange(from,to,range);
			from = {53,153,39,255};
			image->ChangeColourRange(from,to,range);

			//left pattern
			image->CutOutSection(0,0,24,45)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_SideBars_Left");
			//right pattern
			image->CutOutSection(0,776,24,45)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_SideBars_Right");

			//BB Logo
			image->CutOutSection(444,679,58,97)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_BBLogo");
			image->OverwriteSection(442,677,62,101);

			//Game Logo 1
			image->CutOutSection(42,375,279,168)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_Logo");
			//Game Logo 2
			image->CutOutSection(210,304,416,308)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_Logo2");

			delete image;
		}
		else
			Functions::Copy(this->locationofFiles + "s3mcd/install/english/missionm.bmp",this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD.bmp");

		//Buttons
		Functions::Copy(this->locationofFiles + "s3mcd/install/button1.bmp",this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_Button1.bmp");
		Functions::Copy(this->locationofFiles + "s3mcd/install/button2.bmp",this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_Button2.bmp");
	}

	if(this->fileData->GFX->FileReturn("3_60.") != ""){//Mission CD Load Screen only!!
		DataFile*  imageFile = new DataFile(this->locationofGFXFiles + this->fileData->GFX->folder +  this->fileData->GFX->FileReturn("3_60."));
		//Load Screen
		RGBImageData* image = imageFile->ReturnGUIImage(0);
		if(extendible){
			RGBA from = {57,178,8,255};
			RGBA to = {0,0,0,0};
			image->ChangeColour(from,to);
			//Middle Bar
			image->CutOutSection(0,357,314,1)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/MissionCD_MiddleBar");
			//Remove Middle Bar
			//outer1 colour
			from = {16,76,0,255};
			image->ChangeColour(from,to);
			//outer2 colour
			from = {140,230,107,255};
			image->ChangeColour(from,to);
			//Main Colour
			from = {65,206,24,255};
			image->ChangeColour(from,to);
			//extra clean up of Green colour
			from = {24,89,8,255};
			image->ChangeColour(from,to);
			//BB Logo
			image->CutOutSection(494,697,52,87)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/MissionCD_BBLogo");
			image->OverwriteSection(494,697,52,87);
			//Game Logo 1
			image->CutOutSection(161,213,600,451)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX+ this->extractionLocationGUI + "LoadingScreen/MissionCD_Logo");
		}
		else
			image->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/MissionCD");
		delete imageFile;
	}
*/
}

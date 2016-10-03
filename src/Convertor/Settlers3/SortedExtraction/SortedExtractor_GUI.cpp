/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "../SortedExtractor.h"

namespace Extractor {
	namespace Settlers3{
		void SortedExtractor::GUI(bool extendible){
			//Original Menu
			std::string originalMenusFile = this->locationofFiles + this->locationofGFXFiles + this->GFXFileName.first + "02" + this->GFXFileName.second;
			Functions::RGBImage* originalMainMenu = NULL;
			Functions::RGBImage* originalMainMenuButton1 = NULL;
			Functions::RGBImage* originalMainMenuButton2 = NULL;
			Functions::RGBImage* originalMainMenuSideBarsLeft = NULL;
			Functions::RGBImage* originalMainMenuSideBarsRight = NULL;
			Functions::RGBImage* originalMainMenuMiddleBar = NULL;
			Functions::RGBImage* originalMainMenuBBLogo = NULL;
			Functions::RGBImage* originalMainMenuLogo = NULL;
			Functions::RGBImage* originalMainMenuLogo2 = NULL;

			//Original Loading Screen
			Functions::RGBImage* originalLoadingScreen = NULL;
			Functions::RGBImage* originalLoadingScreenMiddleBar = NULL;
			Functions::RGBImage* originalLoadingScreenBBLogo = NULL;
			Functions::RGBImage* originalLoadingScreenLogo = NULL;


			if(Functions::FileExists(originalMenusFile)){

				GFXDataType* file = new GFXDataType(originalMenusFile);
				//menu
				originalMainMenu = file->ReturnGUIImage(5);

				if(extendible){
					//main colour
					RGBA from = {255,93,24,255};
					RGBA to = {0,0,0,0};
					originalMainMenu->ChangeColour(from,to);
					//left pattern
					originalMainMenuSideBarsLeft = new Functions::RGBImage(originalMainMenu->CutOutSection(0,0,38,31),38,31);
					//right pattern
					originalMainMenuSideBarsRight = new Functions::RGBImage(originalMainMenu->CutOutSection(0,769,38,31),38,31);
					//Middle Bar
					originalMainMenuMiddleBar = new Functions::RGBImage(originalMainMenu->CutOutSection(0,390,1,218),1,218);
					//Remove Middle Bar
					//outer1 colour
					from = {123,40,8,255};
					originalMainMenu->ChangeColour(from,to);
					//outer2 colour
					from = {255,157,115,255};
					originalMainMenu->ChangeColour(from,to);
					//outer3 colour
					from = {255,129,74,255};
					originalMainMenu->ChangeColour(from,to);
					from = {255,125,74,255};
					originalMainMenu->ChangeColour(from,to);
					//Main colour
					from = {255,109,49,255};
					originalMainMenu->ChangeColour(from,to);
					//BB Logo
					originalMainMenuBBLogo = new Functions::RGBImage(originalMainMenu->CutOutSection(481,672,83,52),83,52);
					originalMainMenu->OverwriteSection(481,672,83,52);
					//Game Logo 1
					originalMainMenuLogo = new Functions::RGBImage(originalMainMenu->CutOutSection(40,347,183,305),183,305);
					//Game Logo 2
					originalMainMenuLogo2 = new Functions::RGBImage(originalMainMenu->CutOutSection(272,304,288,383),288,383);
				}

				//Buttons
				originalMainMenuButton1 = file->ReturnObjectImage(0,0);
				originalMainMenuButton2 = file->ReturnObjectImage(0,1);


				//Load Screen
				originalLoadingScreen = file->ReturnGUIImage(28);
				if(extendible){
					RGBA from = {255,93,24,255};
					RGBA to = {0,0,0,0};
					originalLoadingScreen->ChangeColour(from,to);
					//Middle Bar
					originalLoadingScreenMiddleBar = new Functions::RGBImage(originalLoadingScreen->CutOutSection(0,357,1,314),1,314);
					//Remove Middle Bar
					//outer1 colour
					from = {123,44,8,255};
					originalLoadingScreen->ChangeColour(from,to);
					//outer2 colour
					from = {255,157,115,255};
					originalLoadingScreen->ChangeColour(from,to);
					//Main Colour
					from = {255,109,49,255};
					originalLoadingScreen->ChangeColour(from,to);
					//extra clean up of orange colour
					//1
					from = {255,129,74,255};
					originalLoadingScreen->ChangeColour(from,to);
					//2
					from = {255,125,74,255};
					originalLoadingScreen->ChangeColour(from,to);
					//3
					from = {255,109,41,255};
					originalLoadingScreen->ChangeColour(from,to);
					//4
					from = {255,105,41,255};
					originalLoadingScreen->ChangeColour(from,to);
					//5
					from = {255,101,32,255};
					originalLoadingScreen->ChangeColour(from,to);
					//6
					from = {255,97,24,255};
					originalLoadingScreen->ChangeColour(from,to);
					//7
					from = {255,93,16,255};
					originalLoadingScreen->ChangeColour(from,to);
					//8
					from = {255,89,24,255};
					originalLoadingScreen->ChangeColour(from,to);
					//9
					from = {255,89,16,255};
					originalLoadingScreen->ChangeColour(from,to);
					//10
					from = {255,85,16,255};
					originalLoadingScreen->ChangeColour(from,to);
					//11
					from = {255,85,8,255};
					originalLoadingScreen->ChangeColour(from,to);
					//BB Logo
					originalLoadingScreenBBLogo = new Functions::RGBImage(originalLoadingScreen->CutOutSection(494,697,87,52),87,52);
					originalLoadingScreen->OverwriteSection(494,697,87,52);
					//Game Logo 1
					originalLoadingScreenLogo = new Functions::RGBImage(originalLoadingScreen->CutOutSection(161,213,451,600),451,600);
				}

				delete file;
			}
/*
			if(this->gameVersion == VersionS3MCD1){//if Mission CD
				if(extendible){
					//Main Colour (58,178,13)
					unsigned short width, height;
					signed short xRel, yRel;
					Functions::FileImage* fileImage = new Functions::FileImage();
					RGBA* imageRGBA = fileImage->LoadImageToRGBA(this->locationofFiles + "s3mcd/install/english/missionm.bmp", &width, &height, &xRel, &yRel);
					delete fileImage;
					RGBImageData* image = new RGBImageData(imageRGBA,height,width,xRel,yRel);
					RGBA from,to,range;

					//Middle Bar
					image->CutOutSection(0,386,1,258)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_MiddleBar");

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
					image->CutOutSection(0,0,45,24)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_SideBars_Left");
					//right pattern
					image->CutOutSection(0,776,45,24)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_SideBars_Right");

					//BB Logo
					image->CutOutSection(444,679,97,58)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_BBLogo");
					image->OverwriteSection(442,677,101,62);

					//Game Logo 1
					image->CutOutSection(42,375,168,279)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_Logo");
					//Game Logo 2
					image->CutOutSection(210,304,308,416)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/MissionCD_Logo2");

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
					image->CutOutSection(0,357,1,314)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/MissionCD_MiddleBar");
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
					image->CutOutSection(494,697,87,52)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/MissionCD_BBLogo");
					image->OverwriteSection(494,697,87,52);
					//Game Logo 1
					image->CutOutSection(161,213,451,600)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX+ this->extractionLocationGUI + "LoadingScreen/MissionCD_Logo");
				}
				else
					image->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/MissionCD");
				delete imageFile;
			}

			if(this->fileData->GFX->FileReturn("3_48.") != ""){//Amazon
				DataFile* imageFile = new DataFile(this->locationofGFXFiles + this->fileData->GFX->folder + this->fileData->GFX->FileReturn("3_48."));
				//Menu
				RGBImageData* image = imageFile->ReturnGUIImage(3);

				if(extendible){
					//main colour
					RGBA from = {140,105,255,255};
					RGBA to = {0,0,0,0};
					image->ChangeColour(from,to);
					//left pattern
					image->CutOutSection(0,0,63,31)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX+ this->extractionLocationGUI + "MainMenu/Amazon_SideBars_Left");
					//right pattern
					image->CutOutSection(0,769,63,31)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_SideBars_Right");
					//BBLogo
					image->CutOutSection(478,671,91,55)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_BBLogo");
					image->OverwriteSection(478,671,91,55);
					//Middle Bar
					image->CutOutSection(0,397,1,204)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_MiddleBar");
					//Remove Middle Bar
					//outer1 colour
					from = {90,68,164,255};
					image->ChangeColour(from,to);
					//outer2 colour
					from = {181,157,255,255};
					image->ChangeColour(from,to);
					//Main colour
					from = {164,133,255,255};
					image->ChangeColour(from,to);
					//Game Logo 1
					image->CutOutSection(13,358,168,280)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_Logo");
					//Game Logo 2
					image->CutOutSection(181,368,407,260)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_Logo2");
				}
				else
					image->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon");

				//Buttons
				imageFile->ReturnObjectImage(0,0)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_Button1");
				imageFile->ReturnObjectImage(0,1)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_Button2");

				//Load Screen
				image = imageFile->ReturnGUIImage(0);
				if(extendible){
					RGBA from = {140,105,255,255};
					RGBA to = {0,0,0,0};
					image->ChangeColour(from,to);
					//Middle Bar
					image->CutOutSection(0,365,1,301)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Amazon_MiddleBar");
					//Remove Middle Bar
					//outer1 colour
					from = {90,68,164,255};
					image->ChangeColour(from,to);
					//outer2 colour
					from = {181,157,255,255};
					image->ChangeColour(from,to);
					//Main colour
					from = {164,133,255,255};
					image->ChangeColour(from,to);
					//BB Logo
					image->CutOutSection(490,734,87,52)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Amazon_BBLogo");
					//Game Logo 1
					image->CutOutSection(257,386,320,260)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Amazon_Logo");
				}
				else
					image->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Amazon");
				delete imageFile;
			}
			if (this->fileData->GFX->FileReturn("3_61.") != ""){//Gold Screens

				DataFile* imageFile = new DataFile(this->locationofGFXFiles + this->fileData->GFX->folder + this->fileData->GFX->FileReturn("3_61."));

				//Main Menu
				RGBImageData* image = imageFile->ReturnGUIImage(2);
				if(extendible){
					//main colour
					RGBA from = {164,149,82,255};
					RGBA to = {0,0,0,0};
					image->ChangeColour(from,to);
					//left pattern
					image->CutOutSection(0,0,62,26)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_SideBars_Left");
					//right pattern
					image->CutOutSection(0,774,62,26)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_SideBars_Right");
					//BBLogo
					image->CutOutSection(476,684,94,55)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_BBLogo");
					image->OverwriteSection(476,684,94,55);
					//Middle Bar
					image->CutOutSection(0,395,1,209)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_MiddleBar");
					//Remove Middle Bar
					//outer1 colour
					from = {107,93,24,255};
					image->ChangeColour(from,to);
					//outer2 colour
					from = {222,206,173,255};
					image->ChangeColour(from,to);
					//Main colour
					from = {189,170,123,255};
					image->ChangeColour(from,to);
					//Game Logo 1
					image->CutOutSection(6,308,269,385)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_Logo");
					//Game Logo 2
					image->CutOutSection(289,305,289,385)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_Logo2");
				}
				else
					image->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold");

				//Buttons
				imageFile->ReturnObjectImage(0,0)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_Button1");
				imageFile->ReturnObjectImage(0,1)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_Button2");

				//Load Screen
				image = imageFile->ReturnGUIImage(0);
				if(extendible){
					//Main Colour
					RGBA from = {164,149,82,255};
					RGBA to = {0,0,0,0};
					image->ChangeColour(from,to);
					//Middle Bar
					image->CutOutSection(0,357,1,314)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Gold_MiddleBar");
					//Remove Middle Bar
					//outer1 colour
					from = {107,93,24,255};
					image->ChangeColour(from,to);
					//outer2 colour
					from = {222,206,173,255};
					image->ChangeColour(from,to);
					//Main colour
					from = {189,170,123,255};
					image->ChangeColour(from,to);
					//Game Logo 1
					image->CutOutSection(114,152,480,732)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Gold_Logo");
				}
				else
					image->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Gold");
				delete imageFile;

				*/
		}
	}
}

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

void Converter::Settlers3::ConvertGUI::Amazon(OSData::GameType* gameType){
/*
	if(this->fileData->GFX->FileReturn("3_48.") != ""){
		DataFile* imageFile = new DataFile(this->locationofGFXFiles + this->fileData->GFX->folder + this->fileData->GFX->FileReturn("3_48."));
		//Menu
		RGBImageData* image = imageFile->ReturnGUIImage(3);
			image->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon");
				image->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Amazon");

			//main colour
			RGBA from = {140,105,255,255};
			RGBA to = {0,0,0,0};
			image->ChangeColour(from,to);
			//left pattern
			image->CutOutSection(0,0,31,63)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX+ this->extractionLocationGUI + "MainMenu/Amazon_SideBars_Left");
			//right pattern
			image->CutOutSection(0,769,31,63)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_SideBars_Right");
			//BBLogo
			image->CutOutSection(478,671,55,91)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_BBLogo");
			image->OverwriteSection(478,671,55,91);
			//Middle Bar
			image->CutOutSection(0,397,204,1)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_MiddleBar");
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
			image->CutOutSection(13,358,280,168)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_Logo");
			//Game Logo 2
			image->CutOutSection(181,368,260,407)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_Logo2");



		//Buttons
		imageFile->ReturnObjectImage(0,0)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_Button1");
		imageFile->ReturnObjectImage(0,1)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Amazon_Button2");

		//Load Screen
		image = imageFile->ReturnGUIImage(0);

			RGBA from = {140,105,255,255};
			RGBA to = {0,0,0,0};
			image->ChangeColour(from,to);
			//Middle Bar
			image->CutOutSection(0,365,301,1)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Amazon_MiddleBar");
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
			image->CutOutSection(490,734,52,87)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Amazon_BBLogo");
			//Game Logo 1
			image->CutOutSection(257,386,260,320)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Amazon_Logo");


		delete imageFile;
	}
*/
}

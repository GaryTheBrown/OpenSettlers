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

void Converter::Settlers3::ConvertGUI::Gold(OSData::GameType* gameType){
/*	if (this->fileData->GFX->FileReturn("3_61.") != ""){

		DataFile* imageFile = new DataFile(this->locationofGFXFiles + this->fileData->GFX->folder + this->fileData->GFX->FileReturn("3_61."));

		//Main Menu
		RGBImageData* image = imageFile->ReturnGUIImage(2);
		if(extendible){
			//main colour
			RGBA from = {164,149,255,82};
			RGBA to = {0,0,0,0};
			image->ChangeColour(from,to);
			//left pattern
			image->CutOutSection(0,0,26,62)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_SideBars_Left");
			//right pattern
			image->CutOutSection(0,774,26,62)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_SideBars_Right");
			//BBLogo
			image->CutOutSection(476,684,55,94)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_BBLogo");
			image->OverwriteSection(476,684,55,94);
			//Middle Bar
			image->CutOutSection(0,395,209,1)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_MiddleBar");
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
			image->CutOutSection(6,308,385,269)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_Logo");
			//Game Logo 2
			image->CutOutSection(289,305,385,289)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "MainMenu/Gold_Logo2");
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
			image->CutOutSection(0,357,314,1)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Gold_MiddleBar");
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
			image->CutOutSection(114,152,732,480)->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Gold_Logo");
		}
		else
			image->SaveToRGBBMP(this->extractionLocation + this->extractionLocationGFX + this->extractionLocationGUI + "LoadingScreen/Gold");
		delete imageFile;
*/
}

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

void Converter::Settlers3::ConvertGUI::Original(OSData::GameType* gameType){
//Original Menu
	std::string originalMenusFile = this->data->locationofFiles + this->data->locationofGFXFiles + this->data->GFXFileName.first + "02" + this->data->GFXFileName.second;

	//Buttons
	Functions::RGBImage* button1 = NULL;
	Functions::RGBImage* button2 = NULL;

	//Original Images
	Functions::RGBImage* mainMenu = NULL;
	Functions::RGBImage* loadingScreen = NULL;

	//Menu Pieces
	Functions::RGBImage* mainMenuSideBarsLeft = NULL;
	Functions::RGBImage* mainMenuSideBarsRight = NULL;
	Functions::RGBImage* mainMenuMiddleBar = NULL;
	Functions::RGBImage* mainMenuBBLogo = NULL;
	Functions::RGBImage* mainMenuLogo = NULL;
	Functions::RGBImage* mainMenuLogo2 = NULL;

	//Loading Screen Pieces
	Functions::RGBImage* loadingScreenMiddleBar = NULL;
	Functions::RGBImage* loadingScreenBBLogo = NULL;
	Functions::RGBImage* loadingScreenLogo = NULL;

	if(Functions::FileExists(originalMenusFile)){

		Extractor::Settlers3::GFXDataType* file = new Extractor::Settlers3::GFXDataType(originalMenusFile);

		//Get Images From File
		//Buttons
		button1 = file->ReturnObjectImage(0,0);
		button2 = file->ReturnObjectImage(0,1);

		//menu
		mainMenu = file->ReturnGUIImage(5);
		//Load Screen
		loadingScreen = file->ReturnGUIImage(28);

		delete file;

		//Main Menu
		//main colour
		RGBA from = {255,93,24,255};
		RGBA to = {0,0,0,0};
		mainMenu->ChangeColour(from,to);
		//left pattern
		mainMenuSideBarsLeft = new Functions::RGBImage(mainMenu->CutOutSection(0,0,31,38),31,38);
		//right pattern
		mainMenuSideBarsRight = new Functions::RGBImage(mainMenu->CutOutSection(0,769,31,38),31,38);
		//Middle Bar
		mainMenuMiddleBar = new Functions::RGBImage(mainMenu->CutOutSection(0,390,218,1),218,1);
		//Remove Middle Bar
		//outer1 colour
		from = {123,40,8,255};
		mainMenu->ChangeColour(from,to);
		//outer2 colour
		from = {255,157,115,255};
		mainMenu->ChangeColour(from,to);
		//outer3 colour
		from = {255,129,74,255};
		mainMenu->ChangeColour(from,to);
		from = {255,125,74,255};
		mainMenu->ChangeColour(from,to);
		//Main colour
		from = {255,109,49,255};
		mainMenu->ChangeColour(from,to);
		//BB Logo
		mainMenuBBLogo = new Functions::RGBImage(mainMenu->CutOutSection(481,672,52,83),52,83);
		mainMenu->OverwriteSection(481,672,52,83);
		//Game Logo 1
		mainMenuLogo = new Functions::RGBImage(mainMenu->CutOutSection(40,347,305,183),305,183);
		//Game Logo 2
		mainMenuLogo2 = new Functions::RGBImage(mainMenu->CutOutSection(272,304,383,288),383,288);

		//Loading Screen
		from = {255,93,24,255};
		to = {0,0,0,0};
		loadingScreen->ChangeColour(from,to);
		//Middle Bar
		loadingScreenMiddleBar = new Functions::RGBImage(loadingScreen->CutOutSection(0,357,314,1),314,1);
		//Remove Middle Bar
		//outer1 colour
		from = {123,44,8,255};
		loadingScreen->ChangeColour(from,to);
		//outer2 colour
		from = {255,157,115,255};
		loadingScreen->ChangeColour(from,to);
		//Main Colour
		from = {255,109,49,255};
		loadingScreen->ChangeColour(from,to);
		//extra clean up of orange colour
		//1
		from = {255,129,74,255};
		loadingScreen->ChangeColour(from,to);
		//2
		from = {255,125,74,255};
		loadingScreen->ChangeColour(from,to);
		//3
		from = {255,109,41,255};
		loadingScreen->ChangeColour(from,to);
		//4
		from = {255,105,41,255};
		loadingScreen->ChangeColour(from,to);
		//5
		from = {255,101,32,255};
		loadingScreen->ChangeColour(from,to);
		//6
		from = {255,97,24,255};
		loadingScreen->ChangeColour(from,to);
		//7
		from = {255,93,16,255};
		loadingScreen->ChangeColour(from,to);
		//8
		from = {255,89,24,255};
		loadingScreen->ChangeColour(from,to);
		//9
		from = {255,89,16,255};
		loadingScreen->ChangeColour(from,to);
		//10
		from = {255,85,16,255};
		loadingScreen->ChangeColour(from,to);
		//11
		from = {255,85,8,255};
		loadingScreen->ChangeColour(from,to);
		//BB Logo
		loadingScreenBBLogo = new Functions::RGBImage(loadingScreen->CutOutSection(494,697,52,87),52,87);
		loadingScreen->OverwriteSection(494,697,52,87);
		//Game Logo 1
		loadingScreenLogo = new Functions::RGBImage(loadingScreen->CutOutSection(161,213,600,451),600,451);


		std::vector<OSData::GUIItemData*>* guiItems= new std::vector<OSData::GUIItemData*>();

		OSData::GUIImageData* MMSideBarsLeft = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(0,0),OSData::GUIItemData::AlignLeft,OSData::GUIItemData::FullTile),mainMenuSideBarsLeft);
		guiItems->push_back(MMSideBarsLeft);
		OSData::GUIImageData* MMSideBarsRight = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::FullTile),mainMenuSideBarsRight);
		guiItems->push_back(MMSideBarsRight);
		OSData::GUIImageData* MMMiddleBar = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(192,0),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::FullStretch),mainMenuMiddleBar);
		guiItems->push_back(MMMiddleBar);
		OSData::GUIImageData* MMBBLogo = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(76,36),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::AlignBottom),mainMenuBBLogo);
		guiItems->push_back(MMBBLogo);
		OSData::GUIImageData* MMLogo = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(148,40),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::pNone),mainMenuLogo);
		guiItems->push_back(MMLogo);
		OSData::GUIImageData* MMLogo2 = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(113,40),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::AlignBottom),mainMenuLogo2);
		guiItems->push_back(MMLogo2);

		OSData::GUITextData* MMVersionText = new OSData::GUITextData(OSData::GUIItemData(std::make_pair(36,5),std::make_pair(0,0),OSData::GUIItemData::pNone,OSData::GUIItemData::AlignBottom),"Version:0.01os",RGBA(255,223,0,255),12);
		guiItems->push_back(MMVersionText);

		std::vector<OSData::GUIItemData*>* boxItems= new std::vector<OSData::GUIItemData*>();

		unsigned short fontSize = 12;
		OSData::GUIButtonData* MMButton1 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Tutorial",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton1);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton2 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Campaign",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton2);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton3 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Mission CD Campaign",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton3);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton4 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Amazon Campaign",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton4);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton5 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Campaign: Normal",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton5);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton6 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Single Player: Scenario",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton6);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton7 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Multi-Player Game: LAN",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton7);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton8 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Multi-Player Game: Internet",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton8);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton9 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Load Game",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton9);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,28)));
		OSData::GUIButtonData* MMButton10 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Online Help",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton10);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton11 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Tips & Tricks",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton11);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton12 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Credits",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMNothing,false);
		boxItems->push_back(MMButton12);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,28)));
		OSData::GUIButtonData* MMButton13 = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone),"Exit Game",RGBA(0,12,66,255),fontSize,button1,button2,button1,MMQuit,false);
		boxItems->push_back(MMButton13);
		OSData::GUIBoxData* MMButtonBox = new OSData::GUIBoxData(OSData::GUIItemData(std::make_pair(60,0),std::make_pair(172,552),OSData::GUIItemData::pNone,OSData::GUIItemData::AlignCentre),RGBA(0,0,0,0),OSData::GUIBoxData::tListView,boxItems,false);
		guiItems->push_back(MMButtonBox);

		OSData::MenuLayout* MLMainMenu = new OSData::MenuLayout(0,"Main Menu - Original",RGBA(255,93,24,255),guiItems);

		gameType->AddMenuLayout(MLMainMenu);

		//TEMP SAVE TO FILES DELETE ONCE MENU LAYOUT IS SETUP


		//Loading Screen
		loadingScreenMiddleBar->SaveToFile("GFX/OLSMiddleBar");
		loadingScreenBBLogo->SaveToFile("GFX/OLSBBLogo");
		loadingScreenLogo->SaveToFile("GFX/OLSLogo");

		//Loading Screen
		if (loadingScreenMiddleBar != NULL)delete loadingScreenMiddleBar;
		if (loadingScreenBBLogo != NULL)delete loadingScreenBBLogo;
		if (loadingScreenLogo != NULL)delete loadingScreenLogo;
		//Original Images
		if (mainMenu != NULL)delete mainMenu;
		if (loadingScreen != NULL)delete loadingScreen;
	}
}

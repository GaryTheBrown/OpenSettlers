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
	std::string GFXFileNameFirstFIX = "s" + this->data->GFXFileName.first.substr(1, this->data->GFXFileName.first.size());
	std::string originalMenusFile = this->data->locationofGFXFiles + GFXFileNameFirstFIX + "61" + this->data->GFXFileName.second;

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
	Functions::RGBImage* loadingScreenLogo = NULL;

	if(Functions::FileExists(originalMenusFile)){
		gameType->AddonsIncluded(OSData::eS3Gold);
		LOGSYSTEM->Log("Gold Main Menu Found Converting...",2);
		this->data->addons = static_cast<OSData::GameAddons>(static_cast<char>(this->data->addons) | static_cast<char>(OSData::eS3Gold));
		Extractor::Settlers3::GFXDataType* file = new Extractor::Settlers3::GFXDataType(originalMenusFile);

		//Buttons
		button1 = file->ReturnObjectImage(0,0);
		button2 = file->ReturnObjectImage(0,1);

		//menu
		mainMenu = file->ReturnGUIImage(2);
		//Load Screen
		loadingScreen = file->ReturnGUIImage(0);
		//Main Menu

		//main colour
		RGBA from = {164,149,82,255};
		RGBA to = {0,0,0,0};
		mainMenu->ChangeColour(from,to);
		//left pattern
		mainMenuSideBarsLeft = mainMenu->CutOutSection(0,0,26,62);
		//right pattern
		mainMenuSideBarsRight = mainMenu->CutOutSection(0,774,26,62);
		//BBLogo
		mainMenuBBLogo = mainMenu->CutOutSection(476,684,55,94);
		mainMenu->OverwriteSection(476,684,55,94);
		//Middle Bar
		mainMenuMiddleBar = mainMenu->CutOutSection(0,395,209,1);
		//Remove Middle Bar
		//outer1 colour
		from = {107,93,24,255};
		mainMenu->ChangeColour(from,to);
		//outer2 colour
		from = {222,206,173,255};
		mainMenu->ChangeColour(from,to);
		//Main colour
		from = {189,170,123,255};
		mainMenu->ChangeColour(from,to);
		//Game Logo 1
		mainMenuLogo = mainMenu->CutOutSection(6,308,385,269);
		//Game Logo 2
		mainMenuLogo2 = mainMenu->CutOutSection(289,305,385,289);

		//Load Screen
		//Main Colour
		from = {164,149,82,255};
		to = {0,0,0,0};
		loadingScreen->ChangeColour(from,to);
		//Middle Bar
		loadingScreenMiddleBar = loadingScreen->CutOutSection(0,357,314,1);
		//Remove Middle Bar
		//outer1 colour
		from = {107,93,24,255};
		loadingScreen->ChangeColour(from,to);
		//outer2 colour
		from = {222,206,173,255};
		loadingScreen->ChangeColour(from,to);
		//Main colour
		from = {189,170,123,255};
		loadingScreen->ChangeColour(from,to);
		//Game Logo 1
		loadingScreenLogo = loadingScreen->CutOutSection(114,152,732,480);


		std::vector<OSData::GUIItemData*>* guiItems= new std::vector<OSData::GUIItemData*>();

		OSData::GUIImageData* MMSideBarsLeft = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(0,0),OSData::GUIItemData::AlignLeft,OSData::GUIItemData::FullTile,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuSideBarsLeft));
		guiItems->push_back(MMSideBarsLeft);
		OSData::GUIImageData* MMSideBarsRight = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::FullTile,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuSideBarsRight));
		guiItems->push_back(MMSideBarsRight);
		OSData::GUIImageData* MMMiddleBar = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(192,0),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::FullStretch,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuMiddleBar));
		guiItems->push_back(MMMiddleBar);
		OSData::GUIImageData* MMBBLogo = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(56,20),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::AlignBottom,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuBBLogo));
		guiItems->push_back(MMBBLogo);
		OSData::GUIImageData* MMLogo = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(103,10),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::pNone,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuLogo));
		guiItems->push_back(MMLogo);
		OSData::GUIImageData* MMLogo2 = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(106,20),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::AlignBottom,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuLogo2));
		guiItems->push_back(MMLogo2);

		OSData::GUITextData* MMVersionText = new OSData::GUITextData(OSData::GUIItemData(std::make_pair(36,5),std::make_pair(0,0),OSData::GUIItemData::pNone,OSData::GUIItemData::AlignBottom,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),"Version:0.01os",RGBA(255,223,0,255),12);
		guiItems->push_back(MMVersionText);

		std::vector<OSData::GUIItemData*>* boxItems= new std::vector<OSData::GUIItemData*>();

		unsigned short fontSize = 12;
		OSData::GUIItemData buttonData = OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone));
		OSData::ImageData blank = OSData::ImageData();


		OSData::GUIButtonData* MMButton1 = new OSData::GUIButtonData(buttonData,"Tutorial",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eAction,ReturnData(GMGotoMenu,0),false);
		boxItems->push_back(MMButton1);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton2 = new OSData::GUIButtonData(buttonData,"Campaign",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eAction,ReturnData(GMGotoMenu,2),false);
		boxItems->push_back(MMButton2);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton3 = new OSData::GUIButtonData(buttonData,"Mission CD Campaign",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eNone,MMNothing,false);
		boxItems->push_back(MMButton3);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton4 = new OSData::GUIButtonData(buttonData,"Amazon Campaign",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eNone,MMNothing,false);
		boxItems->push_back(MMButton4);

		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton5 = new OSData::GUIButtonData(buttonData,"Campaign: Normal",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eNone,MMNothing,false);
		boxItems->push_back(MMButton5);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton6 = new OSData::GUIButtonData(buttonData,"Single Player: Scenario",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eNone,MMNothing,false);
		boxItems->push_back(MMButton6);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton7 = new OSData::GUIButtonData(buttonData,"Multi-Player Game: LAN",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eNone,MMNothing,false);
		boxItems->push_back(MMButton7);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton8 = new OSData::GUIButtonData(buttonData,"Multi-Player Game: Internet",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eNone,MMNothing,false);
		boxItems->push_back(MMButton8);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton9 = new OSData::GUIButtonData(buttonData,"Load Game",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eNone,MMNothing,false);
		boxItems->push_back(MMButton9);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,28)));
		OSData::GUIButtonData* MMButton10 = new OSData::GUIButtonData(buttonData,"Online Help",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eNone,MMNothing,false);
		boxItems->push_back(MMButton10);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton11 = new OSData::GUIButtonData(buttonData,"Tips & Tricks",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eNone,MMNothing,false);
		boxItems->push_back(MMButton11);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton12 = new OSData::GUIButtonData(buttonData,"Credits",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eNone,MMNothing,false);
		boxItems->push_back(MMButton12);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,28)));
		OSData::GUIButtonData* MMButton13 = new OSData::GUIButtonData(buttonData,"Exit Game",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonData::eAction,MMQuit,false);
		boxItems->push_back(MMButton13);
		OSData::GUIBoxData* MMButtonBox = new OSData::GUIBoxData(OSData::GUIItemData(std::make_pair(60,0),std::make_pair(172,552),OSData::GUIItemData::pNone,OSData::GUIItemData::AlignCentre,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),RGBA(0,0,0,0),OSData::GUIBoxData::tListView,boxItems,false);
		guiItems->push_back(MMButtonBox);

		OSData::MenuLayout* MLMainMenu = new OSData::MenuLayout(3,"Main Menu - Gold",RGBA(164,149,82,255),guiItems);

		gameType->AddMenuLayout(MLMainMenu);

		//TEMP SAVE TO FILES DELETE ONCE MENU LAYOUT IS SETUP

		//Loading Screen
		loadingScreenMiddleBar->SaveToFile("GFX/GoldLSMiddleBar");
		loadingScreenLogo->SaveToFile("GFX/GoldLSLogo");

		//Loading Screen
		if (loadingScreenMiddleBar != NULL)delete loadingScreenMiddleBar;
		if (loadingScreenLogo != NULL)delete loadingScreenLogo;
		//Original Images
		if (mainMenu != NULL)delete mainMenu;
		if (loadingScreen != NULL)delete loadingScreen;
	}
}

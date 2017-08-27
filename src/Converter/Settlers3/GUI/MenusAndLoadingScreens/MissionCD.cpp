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

void Converter::Settlers3::ConvertGUI::MissionCD(OSData::GameType* gameType){

	//Mission CD Load Screen Only
	std::string originalMenusFile = this->data->locationofFiles + this->data->locationofGFXFiles + this->data->GFXFileName.first + "60" + this->data->GFXFileName.second;

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

	if(Functions::FileExists(this->data->locationofFiles + "s3mcd/install/english/missionm.bmp")&&Functions::FileExists(this->data->locationofFiles + "s3mcd/install/button1.bmp")&&Functions::FileExists(this->data->locationofFiles + "s3mcd/install/button2.bmp")){
		LOGSYSTEM->Log("Mission CD Main Menu Found Converting...",2);
		this->data->addons = static_cast<OSData::GameAddons>(static_cast<char>(this->data->addons) | static_cast<char>(OSData::eS3MissionCD));
		Functions::FileImage* fileImage = new Functions::FileImage();
		unsigned short* width = new unsigned short(0);
		unsigned short* height = new unsigned short(0);
		RGBA* rgbaImage = fileImage->LoadImageToRGBA(this->data->locationofFiles + "s3mcd/install/english/missionm.bmp", width, height);
		mainMenu = new Functions::RGBImage(rgbaImage,*width,*height);
		//width = new unsigned short(0);
		//height = new unsigned short(0);
		rgbaImage = fileImage->LoadImageToRGBA(this->data->locationofFiles + "s3mcd/install/button1.bmp", width, height);
		button1 = new Functions::RGBImage(rgbaImage,*width,*height);
		//width = new unsigned short(0);
		//height = new unsigned short(0);
		rgbaImage = fileImage->LoadImageToRGBA(this->data->locationofFiles + "s3mcd/install/button2.bmp", width, height);
		button2 = new Functions::RGBImage(rgbaImage,*width,*height);
		delete fileImage;
		RGBA from,to,range;

		//Middle Bar
		mainMenuMiddleBar = mainMenu->CutOutSection(0,386,258,1);

		//Clean Up Green
		range = {64,50,64,0};
		from = {64,205,64,255};
		mainMenu->ChangeColourRange(from,to,range);

		range = {10,10,10,0};
		from = {9,57,0,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {29,90,10,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {39,129,8,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {44,142,14,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {49,172,2,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {73,219,28,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {98,204,62,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {103,217,68,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {129,218,102,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {152,239,125,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {153,242,126,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {10,61,0,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {39,130,8,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {61,187,14,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {46,146,10,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {62,188,14,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {61,186,14,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {60,185,14,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {60,184,14,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {60,183,13,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {59,182,13,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {60,182,13,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {61,185,14,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {61,188,14,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {40,131,8,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {11,63,0,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {29,91,10,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {128,218,101,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {45,144,9,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {68,205,25,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {17,77,2,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {33,103,10,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {158,255,125,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {140,220,106,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {133,235,99,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {67,145,38,255};
		mainMenu->ChangeColourRange(from,to,range);
		from = {53,153,39,255};
		mainMenu->ChangeColourRange(from,to,range);

		//left pattern
		mainMenuSideBarsLeft = mainMenu->CutOutSection(0,0,24,45);
		//right pattern
		mainMenuSideBarsRight = mainMenu->CutOutSection(0,776,24,45);

		//BB Logo
		mainMenuBBLogo = mainMenu->CutOutSection(444,679,58,97);
		mainMenu->OverwriteSection(442,677,62,101);

		//Game Logo 1
		mainMenuLogo = mainMenu->CutOutSection(42,375,279,168);
		//Game Logo 2
		mainMenuLogo2 = mainMenu->CutOutSection(210,304,416,308);
		mainMenuLogo2->OverwriteSection(0,50,200,3);

		std::vector<OSData::GUIItemData*>* guiItems= new std::vector<OSData::GUIItemData*>();

		OSData::GUIImageData* MMSideBarsLeft = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(0,0),OSData::GUIItemData::AlignLeft,OSData::GUIItemData::FullTile,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuSideBarsLeft));
		guiItems->push_back(MMSideBarsLeft);
		OSData::GUIImageData* MMSideBarsRight = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::FullTile,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuSideBarsRight));
		guiItems->push_back(MMSideBarsRight);
		OSData::GUIImageData* MMMiddleBar = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(192,0),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::FullStretch,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuMiddleBar));
		guiItems->push_back(MMMiddleBar);
		OSData::GUIImageData* MMBBLogo = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(76,36),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::AlignBottom,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuBBLogo));
		guiItems->push_back(MMBBLogo);
		OSData::GUIImageData* MMLogo = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(182,40),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::pNone,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuLogo));
		guiItems->push_back(MMLogo);
		OSData::GUIImageData* MMLogo2 = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(113,40),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::AlignBottom,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(mainMenuLogo2));
		guiItems->push_back(MMLogo2);

		OSData::GUITextData* MMVersionText = new OSData::GUITextData(OSData::GUIItemData(std::make_pair(36,5),std::make_pair(0,0),OSData::GUIItemData::pNone,OSData::GUIItemData::AlignBottom,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),"Version:0.01os",RGBA(255,223,0,255),12);
		guiItems->push_back(MMVersionText);

		std::vector<OSData::GUIItemData*>* boxItems= new std::vector<OSData::GUIItemData*>();

		unsigned short fontSize = 12;
		OSData::GUIItemData buttonData = OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone));
		OSData::GUIItemData buttonData2 = OSData::GUIItemData(std::make_pair(0,0),std::make_pair(172,32),OSData::GUIItemData::pNone,OSData::GUIItemData::pNone,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vAddonRequired,OSData::eS3Amazon));
		OSData::ImageData blank = OSData::ImageData();


		OSData::GUIButtonData* MMButton1 = new OSData::GUIButtonData(buttonData,"Tutorial",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eAction),ReturnData(GMGotoMenu,2),false);
		boxItems->push_back(MMButton1);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton2 = new OSData::GUIButtonData(buttonData,"Campaign",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eAction),ReturnData(GMGotoMenu,0),false);
		boxItems->push_back(MMButton2);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton3 = new OSData::GUIButtonData(buttonData,"Mission CD Campaign",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,false);
		boxItems->push_back(MMButton3);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton4 = new OSData::GUIButtonData(buttonData2,"Amazon Campaign",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,false);
		boxItems->push_back(MMButton4);

		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton5 = new OSData::GUIButtonData(buttonData,"Campaign: Normal",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,false);
		boxItems->push_back(MMButton5);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton6 = new OSData::GUIButtonData(buttonData,"Single Player: Scenario",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,false);
		boxItems->push_back(MMButton6);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton7 = new OSData::GUIButtonData(buttonData,"Multi-Player Game: LAN",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,false);
		boxItems->push_back(MMButton7);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton8 = new OSData::GUIButtonData(buttonData,"Multi-Player Game: Internet",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,false);
		boxItems->push_back(MMButton8);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton9 = new OSData::GUIButtonData(buttonData,"Load Game",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,false);
		boxItems->push_back(MMButton9);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,28)));
		OSData::GUIButtonData* MMButton10 = new OSData::GUIButtonData(buttonData,"Online Help",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,false);
		boxItems->push_back(MMButton10);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton11 = new OSData::GUIButtonData(buttonData,"Tips & Tricks",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,false);
		boxItems->push_back(MMButton11);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,8)));
		OSData::GUIButtonData* MMButton12 = new OSData::GUIButtonData(buttonData,"Credits",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,false);
		boxItems->push_back(MMButton12);
		boxItems->push_back(new OSData::GUISpacerData(std::make_pair(0,28)));
		OSData::GUIButtonData* MMButton13 = new OSData::GUIButtonData(buttonData,"Exit Game",RGBA(0,12,66,255),fontSize,button1,button2,blank,OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eAction),MMQuit,false);
		boxItems->push_back(MMButton13);
		OSData::GUIBoxData* MMButtonBox = new OSData::GUIBoxData(OSData::GUIItemData(std::make_pair(60,0),std::make_pair(172,552),OSData::GUIItemData::pNone,OSData::GUIItemData::AlignCentre,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),RGBA(0,0,0,0),OSData::GUIBoxData::tListView,boxItems,false);
		guiItems->push_back(MMButtonBox);

		OSData::MenuLayout* MLMainMenu = new OSData::MenuLayout(1,"Main Menu - Mission CD",RGBA(58,178,13,255),guiItems);

		gameType->AddMenuLayout(MLMainMenu);


	}
	//Loading Screen
	if(Functions::FileExists(originalMenusFile)){
		//This option in here as Main Menu only on Mission CD but GOLD/GOG had all other data files inside)
		gameType->AddonsIncluded(OSData::eS3MissionCD);
		Extractor::Settlers3::GFXDataType* file = new Extractor::Settlers3::GFXDataType(originalMenusFile);
		//Load Screen
		loadingScreen = file->ReturnGUIImage(0);
		delete file;

		RGBA from = {57,178,8,255};
		RGBA to = {0,0,0,0};
		loadingScreen->ChangeColour(from,to);
		//Middle Bar
		loadingScreenMiddleBar = loadingScreen->CutOutSection(0,357,314,1);
		//Remove Middle Bar
		//outer1 colour
		from = {16,76,0,255};
		loadingScreen->ChangeColour(from,to);
		//outer2 colour
		from = {140,230,107,255};
		loadingScreen->ChangeColour(from,to);
		//Main Colour
		from = {65,206,24,255};
		loadingScreen->ChangeColour(from,to);
		//extra clean up of Green colour
		from = {24,89,8,255};
		loadingScreen->ChangeColour(from,to);
		//BB Logo
		loadingScreenBBLogo = loadingScreen->CutOutSection(494,697,52,87);
		loadingScreen->OverwriteSection(494,697,52,87);
		//Game Logo 1
		loadingScreenLogo = loadingScreen->CutOutSection(161,213,600,451);

		std::vector<OSData::GUIImageData*>* loadingImages= new std::vector<OSData::GUIImageData*>();

		OSData::GUIImageData* lsMiddleBar = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(0,0),OSData::GUIItemData::AlignCentre,OSData::GUIItemData::FullStretch,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(loadingScreenMiddleBar));
		loadingImages->push_back(lsMiddleBar);
		OSData::GUIImageData* lsBBLogo = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(76,36),std::make_pair(0,0),OSData::GUIItemData::AlignRight,OSData::GUIItemData::AlignBottom,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(loadingScreenBBLogo));
		loadingImages->push_back(lsBBLogo);
		OSData::GUIImageData* lsLogo = new OSData::GUIImageData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(0,0),OSData::GUIItemData::AlignCentre,OSData::GUIItemData::AlignCentre,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),OSData::ImageData(loadingScreenLogo));
		loadingImages->push_back(lsLogo);

		gameType->AddLoadingScreenLayout(new OSData::LoadingScreenLayout(1,"Loading Screen - Mission CD",RGBA(58,178,13,255),loadingImages));
	}else

	//Delete Original Images
	if (mainMenu != NULL)delete mainMenu;
	if (loadingScreen != NULL)delete loadingScreen;
}

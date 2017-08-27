/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GFXLoadingScreen.h"

GFXInterface::GFXLoadingScreen::GFXLoadingScreen(SystemInterface::System* system, ConfigList* configList, OSData::LoadingScreenLayout* loadingScreenLayout, OSData::GameAddons addons){
	if(loadingScreenLayout != NULL){
		this->system = system;
		this->configList = configList;
		this->loadingScreenLayout = loadingScreenLayout;
		this->title = this->loadingScreenLayout->Title();
		this->backgroundColour = this->loadingScreenLayout->BackgroundColour();
		this->imageList = new std::vector<GFXImage*>();

		if(this->loadingScreenLayout->ImageData() != NULL){
			GFXImage* image;
			for(auto item=this->loadingScreenLayout->ImageData()->begin() ; item < this->loadingScreenLayout->ImageData()->end(); item++ ){
				image = new GFXImage(this->system,this->configList,(OSData::GUIImageData*)(*item),addons);
				this->imageList->push_back(image);
			}
		}
	}
}
GFXInterface::GFXLoadingScreen::~GFXLoadingScreen() {
	if (this->imageList != NULL) {
		for(auto item=this->imageList->begin() ; item < this->imageList->end(); item++ ){
			delete (*item);
		}
		this->imageList->clear();
		delete this->imageList;
	}
}

void GFXInterface::GFXLoadingScreen::Draw(){

    this->system->display->ClearToColour(this->backgroundColour);
	if(this->imageList != NULL){
		for(auto item=this->imageList->begin() ; item < this->imageList->end(); item++ ){
			(*item)->Draw();
		}
	}
	this->system->display->FlipScreen();
}

void GFXInterface::GFXLoadingScreen::ResizedWindow(){
	if(this->imageList != NULL){
		for(auto item=this->imageList->begin() ; item < this->imageList->end(); item++ ){
			(*item)->CalculateLocation();
		}
	}
}
/*
ReturnData GFXInterface::GFXLoadingScreen::EventHandler(){
	//Handle events on queue
	while(this->system->events->GetNextEvent()){
		switch(this->system->events->GetEvent()){
		//User presses Quit Button
		case SystemInterface::eQuit:
			return MMQuit;
		//User presses a key
		case SystemInterface::eKeyboardDown:
		    //Select surfaces based on key press
		    switch( this->system->events->GetKey()){
		    case SystemInterface::KEYBOARD_ESCAPE:
		    	return MMQuit;
		    case SystemInterface::KEYBOARD_F10:
		    	this->system->display->SetWindowFullscreen();
		    	this->ResizedWindow();
		    	break;
		    default:
		    	break;
		    }
		    break;
		//User uses The Mouse
		case SystemInterface::eMouseMotion:
		case SystemInterface::eMouseButtonDown:
		case SystemInterface::eMouseButtonUp:
		case SystemInterface::eMouseWheel:
		  	if(this->itemList != NULL){
		   		//Works Backwards through Items to work from top down
		   		ReturnData returnEvent = MMNothing;
		   		for(auto item=this->itemList->end() -1 ; item > this->itemList->begin() -1; item-- ){
	    			switch((*item)->GetItemType()){
	    			case OSData::GUIItemData::GUIButtonType:
	    			case OSData::GUIItemData::GUIBoxType:
	    				returnEvent = (*item)->EventHandler();
						switch(returnEvent.LoadingScreenEvent()){
							case MMNothing:
								break;
							//case CLDisplayAll:

							//break;
							case CLSingleOption:
								if(returnEvent.String() == "FULLSCREEN"){
									this->system->display->SetWindowFullscreen();
								}else if(returnEvent.String() == "WINDOWSIZE"){
									auto windowSize = this->configList->GetValue<std::pair<int,int> >("windowsize");
									this->system->display->SetWindowSize(windowSize);
								}
								else if(returnEvent.String() == "SHOWFPS"){
									bool showfps = this->configList->GetValue<bool>("showfps");
									if(showfps){
										this->system->display->ShowFPS();
									}else{
										this->system->display->HideFPS();
									}
								}

								//returnEvent.String()//option code
								break;
							default:
								return returnEvent;
						}
	    				break;
	    			default:
	    				break;
	    			}
	    		}
	    	}
	    	break;
	    case SystemInterface::eWindowResized:{
	    	//CHECK WINDOW SIZE AND IF BELOW MIN SET TO MIN
	   	    std::pair<int,int> tempSize = this->system->events->GetResizedWindowSize();

	   	    if(tempSize.first < this->system->display->GetWindowMINSize().first) tempSize.first = this->system->display->GetWindowMINSize().first;
	   	    if(tempSize.second < this->system->display->GetWindowMINSize().second) tempSize.second = this->system->display->GetWindowMINSize().second;

 			this->system->display->SetWindowSize(tempSize);

//			this->configList->SetValue("windowSize",tempSize);
//	   	    this->system->display->SetWindowSize();

	   	    this->ResizedWindow();
	   	    break;
	    }
	    default:
	    	break;
		}
	}
	return MMNothing;
}

ReturnData GFXInterface::GFXLoadingScreen::Loop(){

	while (true){

		this->system->display->FPSRestart();

		ReturnData event = this->EventHandler();
		switch (event.LoadingScreenEvent()){
		//Commands ran outside of LoadingScreen
		case MMStartGame:
			for(auto item=this->itemList->begin() ; item < this->itemList->end(); item++ ){
				if ((*item)->GetItemType() == OSData::GUIItemData::GUIBoxType){
					GFXItem* fetched = (*item)->GetSelected();
					if(fetched != NULL){
						return ReturnData(event.LoadingScreenEvent(),fetched->GetText());
					}
				}
			}
			break;
		case MMAddGame:
		case MMEditGame:
		case MMQuit:
		case GMGotoLoadingScreen:
		case MMOptions: //TMP
			return event;

		//Functions inside LoadingScreen system
		case MMAbout:
			if(this->system->display->GetShowFPS() == false){
				this->system->display->ShowFPS();
			}
			else {
				this->system->display->HideFPS();
				this->system->display->SetWindowName();
			}
			break;
	    // if nothing or not recognised
	    case MMNothing:
	    default:
	    	break;
		}

		//Clear screen
	    this->system->display->ClearToColour(this->backgroundColour);

	    //Render texture to screen
	    this->Draw();

	    //Update screen
	    this->system->display->FlipScreen();

	    this->system->display->ShowFPSCounter();

	    this->system->display->FPSWait();
	}
	return ReturnData(MMNothing);
}
*/
/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GFXMenu.h"

GFXInterface::GFXMenu::GFXMenu(SystemInterface::System* system, OSData::MenuLayout* menuLayout, OSData::GameAddons addons){
	if(menuLayout != NULL){
		this->system = system;
		this->menuLayout = menuLayout;
		this->title = this->menuLayout->Title();
		this->backgroundColour = this->menuLayout->BackgroundColour();
		this->itemList = new std::vector<GFXItem*>();

		if(this->menuLayout->ItemData() != NULL){
			GFXImage* image;
			GFXButton* button;
			GFXBox* box;
			GFXText* text;
			GFXSpacer* spacer;
			for(auto item=this->menuLayout->ItemData()->begin() ; item < this->menuLayout->ItemData()->end(); item++ ){
				switch ((*item)->ItemType()){
				default:
					break;
				case OSData::GUIItemData::GUIImageType:
					image = new GFXImage(this->system,(OSData::GUIImageData*)(*item),addons);
					this->itemList->push_back(image);
					break;
				case OSData::GUIItemData::GUIButtonType:
					button = new GFXButton(this->system,(OSData::GUIButtonData*)(*item),addons);
					this->itemList->push_back(button);
					break;
				case OSData::GUIItemData::GUIBoxType:
					box = new GFXBox(this->system,(OSData::GUIBoxData*)(*item),addons);
					this->itemList->push_back(box);
					break;
				case OSData::GUIItemData::GUITextType:
					text = new GFXText(this->system,(OSData::GUITextData*)(*item),addons);
					this->itemList->push_back(text);
					break;
				case OSData::GUIItemData::GUISpacerType:
					spacer = new GFXSpacer(this->system,(OSData::GUISpacerData*)(*item));
					this->itemList->push_back(spacer);
					break;
				}
			}
		}
	}
}
GFXInterface::GFXMenu::~GFXMenu() {
	if (this->itemList != NULL) {
		for(auto item=this->itemList->begin() ; item < this->itemList->end(); item++ ){
			delete (*item);
		}
		this->itemList->clear();
		delete this->itemList;
	}
}

void GFXInterface::GFXMenu::Draw(){

    this->system->display->ClearToColour(this->backgroundColour);
	if(this->itemList != NULL){
		for(auto item=this->itemList->begin() ; item < this->itemList->end(); item++ ){
			(*item)->Draw();
		}
	}
	this->system->display->FlipScreen();
}

void GFXInterface::GFXMenu::ResizedWindow(){
	if(this->itemList != NULL){
		for(auto item=this->itemList->begin() ; item < this->itemList->end(); item++ ){
			(*item)->CalculateLocation();
		}
	}
}

ReturnData GFXInterface::GFXMenu::EventHandler(){
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
	    				if (returnEvent != ReturnData(MMNothing)) return returnEvent;
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

	   	    this->ResizedWindow();
	   	    break;
	    }
	    default:
	    	break;
		}
	}
	return MMNothing;
}

ReturnData GFXInterface::GFXMenu::Loop(){

	while (true){

		this->system->display->FPSRestart();

		ReturnData event = this->EventHandler();
		switch (event.MenuEvent()){
		//Commands ran outside of menu
		case MMStartGame:
			for(auto item=this->itemList->begin() ; item < this->itemList->end(); item++ ){
				if ((*item)->GetItemType() == OSData::GUIItemData::GUIBoxType){
					GFXItem* fetched = (*item)->GetSelected();
					if(fetched != NULL){
						return ReturnData(event.MenuEvent(),fetched->GetText());
					}
				}
			}
			break;
		case MMAddGame:
		case MMEditGame:
		case MMQuit:
		case GMGotoMenu:
		case MMOptions: //TMP
			return event;

		//Functions inside menu system
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

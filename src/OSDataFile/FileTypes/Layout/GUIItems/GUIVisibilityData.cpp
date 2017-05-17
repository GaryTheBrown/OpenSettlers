/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIVisibilityData.h"
OSData::GUIVisibilityData::GUIVisibilityData(VisibilityOptions type):type(type){

}

OSData::GUIVisibilityData::GUIVisibilityData(VisibilityOptions type, bool visible, bool enabled):
		type(type),
		visible(visible),
		enabled(enabled){


}
OSData::GUIVisibilityData::GUIVisibilityData(VisibilityOptions type, OSData::GameAddons addonRequired):
	type(type),
	addonRequired(addonRequired){

}

OSData::GUIVisibilityData::GUIVisibilityData(Functions::DataReader* reader){
	this->type = static_cast<VisibilityOptions>(reader->ReadChar());
	switch(this->type){
	default:
		break;
	case vBasic:
		this->visible = reader->ReadChar();
		this->enabled = reader->ReadChar();
		break;
	case vAddonRequired:
		this->addonRequired = static_cast<GameAddons>(reader->ReadChar());
		break;
	}
}

void OSData::GUIVisibilityData::CheckItemValues(std::string name, std::string value){
	if (name == "Visible")
		this->visible = true;
	else if (name == "Hidden")
		this->visible = false;
	else if (name == "Enabled")
		this->enabled = true;
	else if (name == "Disabled")
		this->enabled = false;
	else if (name == "AddonRequired")
		this->addonRequired = AddonDataFromText(value);
}

bool OSData::GUIVisibilityData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) return false;
	// This order
	//Type (char)
	data->push_back(static_cast<char>(this->type));

	switch(this->type){
		default:
			break;
		case vBasic:
			data->push_back(this->visible?0:1);
			data->push_back(this->enabled?0:1);
			break;
		case vAddonRequired:
			data->push_back(static_cast<char>(this->addonRequired));
			break;
		}

	return true;
}
std::string OSData::GUIVisibilityData::ToString(){
	std::string data;
	switch(this->type){
	default:
		break;
	case vBasic:
		data += "Visibility = " + (this->visible?std::string("true"):std::string("false")) + "\n";
		data += "Enabled = " + (this->enabled?std::string("true"):std::string("false")) + "\n";
		break;
	case vAddonRequired:
		data += "Requires = ";
		data += ((this->addonRequired & OSData::eS2MissionCD)?"S2MCD ":"");
		data += ((this->addonRequired & OSData::eS2Gold)?"S2GOLD ":"");
		data += ((this->addonRequired & OSData::eS3MissionCD)?"S3MCD ":"");
		data += ((this->addonRequired & OSData::eS3Amazon)?"S3AMAZON ":"");
		data += ((this->addonRequired & OSData::eS3Gold)?"S3GOLD ":"");
		data += ((this->addonRequired & OSData::eS4MissionCD)?"S4MCD ":"");
		data += ((this->addonRequired & OSData::eS4Trojan)?"S4TROJAN ":"");
		data += ((this->addonRequired & OSData::eS4Gold)?"S4GOLD ":"");
		data += ((this->addonRequired & OSData::eS4NewWorld)?"S4NEWWORLD ":"");
		data += ((this->addonRequired & OSData::eS4Community)?"S4COMMUNITY ":"");
		data +=  "\n";
		break;
	}

	return data;
}

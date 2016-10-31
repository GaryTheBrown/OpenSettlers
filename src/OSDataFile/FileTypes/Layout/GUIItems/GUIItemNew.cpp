/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIItemNew.h"

OSData::GUIItemData::eGUIItemType OSData::GetItemType(std::string data){
	if (data == "GUIImage"){
		return GUIItemData::GUIImageType;
	} else if (data == "GUIButton"){
		return GUIItemData::GUIButtonType;
	} else if (data == "GUIText"){
		return GUIItemData::GUITextType;
	} else if (data == "GUIBox"){
		return GUIItemData::GUIBoxType;
	} else if (data == "GUISpacer"){
		return GUIItemData::GUISpacerType;
	}
	return GUIItemData::GUINoneType;
}

OSData::GUIItemData* OSData::DoItemType(GUIItemData::eGUIItemType itemDataType, void* data,bool xml){

	switch(itemDataType){
	case GUIItemData::GUIImageType:
		if(xml){
			return new GUIImageData((xmlNode*)data);
		}else{
			return new GUIImageData((Functions::DataReader*)data);
		}
		break;
	case GUIItemData::GUIButtonType:
		if(xml){
			return new GUIButtonData((xmlNode*)data);
		}else{
			return new GUIButtonData((Functions::DataReader*)data);
		}
		break;
	case GUIItemData::GUITextType:
		if(xml){
			return new GUITextData((xmlNode*)data);
		}else{
			return new GUITextData((Functions::DataReader*)data);
		}
		break;
	case GUIItemData::GUIBoxType:
		if(xml){
			return new GUIBoxData((xmlNode*)data);
		}else{
			return new GUIBoxData((Functions::DataReader*)data);
		}
		break;
	case GUIItemData::GUISpacerType:
		if(xml){
			return new GUISpacerData((xmlNode*)data);
		}else{
			return new GUISpacerData((Functions::DataReader*)data);
		}
		break;
	default:{
		return NULL;
		break;
	}
	}
}


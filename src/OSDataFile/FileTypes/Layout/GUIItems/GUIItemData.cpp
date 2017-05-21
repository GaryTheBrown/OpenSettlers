/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIItemData.h"
OSData::GUIItemData::GUIItemData(std::pair<unsigned short,unsigned short> location,std::pair<unsigned short,unsigned short> size,ePosition horizontalPosition,ePosition verticalPosition,GUIVisibilityData visibilityData)
	:itemType(GUINoneType),
	location(location),
	size(size),
	horizontalPosition(horizontalPosition),
	verticalPosition(verticalPosition),
	visibilityData(visibilityData){
}
OSData::GUIItemData::GUIItemData(eGUIItemType itemType,GUIItemData baseData)
	:itemType(itemType),
	location(baseData.Location()),
	size(baseData.Size()),
	horizontalPosition(baseData.Horizontal()),
	verticalPosition(baseData.Vertical()),
	visibilityData(baseData.VisibilityData()){
}

OSData::GUIItemData::GUIItemData(eGUIItemType itemType,Functions::DataReader* reader):itemType(itemType){

	this->APIVersion = reader->ReadInt();

	if (this->APIVersion > APILEVEL::GUIITEMS){
			LOGSYSTEM->Error("Item API is Newer than Game API:" + Functions::ToString(this->APIVersion) + ">" + Functions::ToString(APILEVEL::GUIITEMS));
			 this->fileOK = false;
			 return;
	}
	this->location.first = reader->ReadShort();
	this->location.second = reader->ReadShort();
	this->size.first = reader->ReadShort();
	this->size.second = reader->ReadShort();
	this->horizontalPosition = static_cast<ePosition>(reader->ReadChar());
	this->verticalPosition = static_cast<ePosition>(reader->ReadChar());
	this->visibilityData = OSData::GUIVisibilityData(reader);

}
OSData::GUIItemData::GUIItemData(eGUIItemType itemType,xmlNode* node):itemType(itemType){
	if(node != NULL){
		xmlAttr* xmlAttribute = node->properties;
		while(xmlAttribute){
			this->CheckItemValues(((char*)xmlAttribute->name),((char*)xmlAttribute->children->content));
			xmlAttribute = xmlAttribute->next;
		}

//		xmlNode* itemNode = node->children;
//		while(itemNode){
//			this->CheckItemValues(((char*)itemNode->name),((char*)itemNode->content));
//			itemNode = itemNode->next;
//		}
	}
}
void OSData::GUIItemData::CheckItemValues(std::string name, std::string value){
	if (name == "VerticalPosition")
		this->verticalPosition = this->GetPositionType(value);
	else if (name == "HorizontalPosition")
		this->horizontalPosition = this->GetPositionType(value);
	else if (name == "VerticalLocation")
		this->location.second = atoi(value.c_str());
	else if (name == "HorizontalLocation")
		this->location.first = atoi(value.c_str());
	else if (name == "HorizontalSize")
		this->size.first = atoi(value.c_str());
	else if (name == "VerticalSize")
		this->size.second = atoi(value.c_str());
}
OSData::GUIItemData::ePosition OSData::GUIItemData::GetPositionType(std::string data){
	if (data == "AlignLeft") return AlignLeft;
	if (data == "AlignTop")	return AlignTop;
	if (data == "AlignRight") return AlignRight;
	if (data == "AlignBottom") return AlignBottom;
	if (data == "AlignCentre") return AlignCentre;
	if (data == "FullTile ") return FullTile;
	if (data == "FullStretch") return FullStretch;
	if (data == "StretchSetSize") return StretchSetSize;
	if (data == "StretchFromFrom") return StretchFromFrom;
	if (data == "StretchPercent") return StretchPercent;
	if (data == "AlignTL") return AlignTL;
	if (data == "AlignBR") return AlignBR;

	//if (data == "None")
	return pNone;

}

bool OSData::GUIItemData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) return false;
	// This order
	//itemType (char)
	data->push_back(static_cast<char>(this->itemType));

	//API Version (int)
	data->push_back(this->APIVersion & 0xFF);
	data->push_back((this->APIVersion >> 8) & 0xFF);
	data->push_back((this->APIVersion >> 16) & 0xFF);
	data->push_back((this->APIVersion >> 24) & 0xFF);

	//location.first (Short)
	data->push_back(this->location.first & 0xFF);
	data->push_back((this->location.first >> 8) & 0xFF);

	//location.second (Short)
	data->push_back(this->location.second & 0xFF);
	data->push_back((this->location.second >> 8) & 0xFF);

	//size.first (Short)
	data->push_back(this->size.first & 0xFF);
	data->push_back((this->size.first >> 8) & 0xFF);

	//size.second (Short)
	data->push_back(this->size.second & 0xFF);
	data->push_back((this->size.second >> 8) & 0xFF);


	//Horizontal Position (Char)
	data->push_back(static_cast<char>(this->horizontalPosition));
	//Vertical Position (Char)
	data->push_back(static_cast<char>(this->verticalPosition));

	//Visible Data
	this->visibilityData.ToSaveToData(data);
	return true;
}

std::string OSData::GUIItemData::ToString(){
	std::string data;
	data += "Location.X = " + Functions::ToString(this->location.first) + "\n";
	data += "Location.Y = " + Functions::ToString(this->location.second) + "\n";
	data += "Size.X = " + Functions::ToString(this->size.first) + "\n";
	data += "Size.Y = " + Functions::ToString(this->size.second) + "\n";
	data += "Horizontal Position = ";
	switch(this->horizontalPosition){
	case AlignLeft:
		data += "AlignLeft";
		break;
	case AlignRight:
		data += "AlignRight";
		break;
	case AlignCentre:
		data += "AlignCentre";
		break;
	case FullTile:
		data += "FullTile";
		break;
	case FullStretch:
		data += "FullStretch";
		break;
	case StretchSetSize:
		data += "StretchSizeSize";
		break;
	case StretchFromFrom:
		data += "StretchFromFrom";
		break;
	case StretchPercent:
		data += "StretchPercent";
		break;
	default:
	case pNone:
		data += "None";
		break;
	}
	data += "\n";

	data += "Vertical Position = ";
	switch(this->verticalPosition){
	case AlignTop:
		data += "AlignTop";
		break;
	case AlignBottom:
		data += "AlignBottom";
		break;
	case AlignCentre:
		data += "AlignCentre";
		break;
	case FullTile:
		data += "FullTile";
		break;
	case FullStretch:
		data += "FullStretch";
		break;
	case StretchSetSize:
		data += "StretchSetSize";
		break;
	case StretchFromFrom:
		data += "StretchFromFrom";
		break;
	case StretchPercent:
		data += "StretchPercent";
		break;
	default:
	case pNone:
		data += "None";
		break;
	}
	data += "\n";

	return data;
}

/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "GUIBoxData.h"

OSData::GUIBoxData::GUIBoxData(GUIItemData baseData, RGBA backgroundColour, eBoxType boxType, std::vector<GUIItemData*>* itemDataList,bool multiSelect)
	:OSData::GUIItemData(GUIBoxType,baseData){
	this->backgroundColour = backgroundColour;
	this->boxType = boxType;
    this->itemData = itemDataList;
    this->multiSelect = multiSelect;
}

OSData::GUIBoxData::GUIBoxData(Functions::DataReader* reader)
	:OSData::GUIItemData(GUIBoxType,reader){

	this->backgroundColour = reader->ReadInt();
	this->boxType = static_cast<eBoxType>(reader->ReadChar());
	this->multiSelect = reader->ReadChar() & 1;

	switch(this->boxType){
		case tGridView:
		case tListView:
		case tFreeView:{
			unsigned short count = reader->ReadShort();
			this->itemData = new std::vector<GUIItemData*>();
			for (unsigned char i = 0; i < count; i++){
				eGUIItemType itemDataType = static_cast<eGUIItemType>(reader->ReadChar());
				this->itemData->push_back(DoItemType(itemDataType,reader));
			}
			break;
		}
		case tListFullDir:
		case tListFolderDir:
		case tListFileDir:{
			this->directoryData = new GUIBoxDirectoryData(reader);
			this->DirCreation();
			break;
		}
		case tEmpty:
		default:{
			break;
		}
	}
}
OSData::GUIBoxData::GUIBoxData(xmlNode* node):GUIItemData(GUIBoxType,node){
	if(node != NULL){
		xmlAttr* xmlAttribute = node->properties;
		while(xmlAttribute){
			this->CheckValues(((char*)xmlAttribute->name),((char*)xmlAttribute->children->content));
			xmlAttribute = xmlAttribute->next;
		}

//		xmlNode* itemNode = node->children;
//		while(itemNode){
//			this->CheckValues(((char*)itemNode->name),((char*)itemNode->content));
//			itemNode = itemNode->next;
//		}

		switch(this->boxType){
			case tGridView:
			case tListView:
			case tFreeView:{
				xmlNode* itemNode = node->children;
				if(itemNode != NULL){
					this->itemData = new std::vector<GUIItemData*>();
					while(itemNode){
						GUIItemData::eGUIItemType itemDataType = GetItemType((char*)itemNode->name);
						if (itemDataType != GUIItemData::GUINoneType)
							this->itemData->push_back(DoItemType(itemDataType,itemNode,true));
						itemNode = itemNode->next;
					}
				}
				break;
			}
			case tListFullDir:
			case tListFolderDir:
			case tListFileDir:{
				std::string tmpName = (char*)node->children->name;
				if (tmpName == "DirInfo"){
					this->directoryData = new GUIBoxDirectoryData(node->children);
					this->DirCreation();
				}
				break;
			}
			case tEmpty:
			default:{
				break;
			}
		}
	}
}

OSData::GUIBoxData::~GUIBoxData(){
	if(this->itemData != NULL){
		for(auto item=this->itemData->begin() ; item < this->itemData->end(); item++ ){
			delete (*item);
		}
		this->itemData->clear();
		delete this->itemData;
	}
	if(this->directoryData != NULL)
		delete this->directoryData;
};

void OSData::GUIBoxData::GetBoxType(std::string data){
	if (data == "GridView")
		this->boxType = tGridView;
	else if (data == "ListView")
		this->boxType = tListView;
	else if (data == "FreeView")
		this->boxType = tFreeView;
	else if (data == "ListFullDir")
		this->boxType = tListFullDir;
	else if (data == "ListFolderDir")
		this->boxType = tListFolderDir;
	else if (data == "ListFileDir")
		this->boxType = tListFileDir;
	else
		this->boxType = tEmpty;
}

void OSData::GUIBoxData::CheckValues(std::string name, std::string value){
	if (name == "ListBoxType")
		this->GetBoxType(value);
	else if (name == "BackgroundColour")
		this->backgroundColour = Functions::StringToHex(value);
	else if (name == "MultiSelect")
		this->multiSelect = (value=="true")?true:false;
}

void OSData::GUIBoxData::DirCreation(){
	std::vector<std::string>* list;
	switch(this->boxType){
		case tListFileDir:
			list = Functions::GetFilesInDirectory(this->directoryData->FolderLocation());
			break;
		case tListFolderDir:
			list = Functions::GetFoldersInDirectory(this->directoryData->FolderLocation());
			break;
		case tListFullDir:
		default:
			list = Functions::GetFullDirectory(this->directoryData->FolderLocation());
			break;
	}
	if (this->directoryData != NULL){
		this->itemData = new std::vector<GUIItemData*>();
		for(auto item = list->begin() ; item < list->end(); item++ ){
			GUIItemData* button = new OSData::GUIButtonData(OSData::GUIItemData(std::make_pair(0,0),std::make_pair(1,this->directoryData->VerticalSize()),GUIButtonData::pNone,GUIButtonData::pNone,OSData::GUIVisibilityData(OSData::GUIVisibilityData::vNone)),(*item),this->directoryData->TextColour(),this->directoryData->FontSize(),OSData::ImageData(RGBA(0,0,0,0)),this->directoryData->SelectColour(),OSData::ImageData(),OSData::GUIButtonTypeData(OSData::GUIButtonTypeData::eNone),MMNothing,true);
			this->itemData->push_back(button);
		}
		delete list;
	}
}

bool OSData::GUIBoxData::ToSaveToData(std::vector<char>* data){
	if (data == NULL) data = new std::vector<char>;
	if (GUIItemData::ToSaveToData(data) == false) return false;

	//Background Colour (Int)(RGBA)
	data->push_back(this->backgroundColour.A);
	data->push_back(this->backgroundColour.B);
	data->push_back(this->backgroundColour.G);
	data->push_back(this->backgroundColour.R);

	//Box Type (Short)(eBoxType)----
	data->push_back(static_cast<char>(this->boxType));

	//Multi Select (Bool)
	data->push_back(this->multiSelect?1:0);

	switch(this->boxType){
			case tGridView:
			case tListView:
			case tFreeView:{
				if (this->itemData != NULL){
					//Item count (Char)
					unsigned short count = this->itemData->size();
					data->push_back(count & 0xFF);
					data->push_back((count >> 8) & 0xFF);

					for(auto item=this->itemData->begin() ; item < this->itemData->end(); item++ ){
						(*item)->ToSaveToData(data);
					}
				} else{
					data->push_back(0);
					data->push_back(0);
					LOGSYSTEM->Error("SAVE::Box Item Data empty");
				}
				break;
			}
			case tListFullDir:
			case tListFolderDir:
			case tListFileDir:{
				if (this->directoryData != NULL)
					this->directoryData->ToSaveToData(data);
				break;
			}
			case tEmpty:
			default:
				break;
		}
	return true;
}

bool OSData::GUIBoxData::ImageToNumbers(std::vector<Functions::RGBImage*>* images, std::vector<std::string>* imageLocations){
	if (images == NULL) return false;

	//TODO ADD in system for Image Data here once data above updated
	for(auto item = this->itemData->begin(); item != this->itemData->end(); item++) {
		switch((*item)->ItemType()){
		case GUIItemData::GUIBoxType:
		case GUIItemData::GUIButtonType:
		case GUIItemData::GUIImageType:
			if((*item)->ImageToNumbers(images,imageLocations) == false) return false;
			break;
		default:
			break;
		}
	}
	return true;
}

bool OSData::GUIBoxData::LinkNumbers(std::vector<Functions::RGBImage*>* images){
	if (images == NULL) return false;

	for(auto item = this->itemData->begin(); item != this->itemData->end(); item++) {
		switch((*item)->ItemType()){
		case GUIItemData::GUIBoxType:
		case GUIItemData::GUIButtonType:
		case GUIItemData::GUIImageType:
			if((*item)->LinkNumbers(images) == false) return false;
			break;
		default:
			break;
		}
	}
	return true;
}
std::string OSData::GUIBoxData::ToString(){
	std::string data;
	data += "GUIBOX\n";
	data += GUIItemData::ToString();

	data += "Background Colour = " + Functions::ToHex(this->backgroundColour.ReturnInt(),4) + "\n";
	data += "Multi Select = " + (this->multiSelect?std::string("True"):std::string("False")) + "\n";
	switch(this->boxType){
		case tGridView:
		case tListView:
		case tFreeView:{
			switch(this->boxType){
				case tGridView:
					data += "Box Type = Grid View\n";
					break;
				case tListView:
					data += "Box Type = List View\n";
					break;
				case tFreeView:
					data += "Box Type = Free View\n";
					break;
				default:
					break;
			}
			if (this->itemData != NULL){
				for(auto item=this->itemData->begin() ; item < this->itemData->end(); item++ ){
					data += (*item)->ToString();
				}
			}
			break;
		}
		case tListFullDir:
		case tListFolderDir:
		case tListFileDir:{
			switch(this->boxType){
				case tListFullDir:
					data += "Box Type = List Full Directory\n";
					break;
				case tListFolderDir:
					data += "Box Type = List Folder Directory\n";
					break;
				case tListFileDir:
					data += "Box Type = List File Directory\n";
					break;
				default:
					break;
			}
			if (this->directoryData != NULL)
				data += this->directoryData->ToString();
			break;
		}
		case tEmpty:
		default:
			break;
	}

	return data;
}

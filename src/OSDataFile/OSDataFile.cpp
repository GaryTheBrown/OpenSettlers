/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "OSDataFile.h"

OSData::File::File(std::string file){

	if (Functions::FileExists(file) == false){
		LOGSYSTEM->Error(file + " not Found");
		this->fileOK = false;
		return;
	};

	std::string extension = file.substr(file.find_last_of(".") + 1);
	std::transform(extension.begin(), extension.end(), extension.begin(), toupper);

	if (extension == "DAT"){
		this->ConstructFromDataFile(file);
	}else if (extension == "XML"){
		this->ConstructFromXMLFile(file);
	}
}

OSData::File::File(FileTypes* data):dataType(data){
	if (data == NULL){
		LOGSYSTEM->Error("Data Empty");
		this->fileOK = false;
		return;
	}
}

void OSData::File::ConstructFromDataFile(std::string file){

	Functions::DataReader* reader = new Functions::DataReader(file);
	std::string headCode = reader->ReadString(4);
	if (headCode != "OSET"){
		LOGSYSTEM->Error(file + " is not an Open Settlers File. Getting: " + headCode);
		this->fileOK = false;
		return;
	}
	this->APIVersion = 0;
	reader->ReadInt();
	if (this->APIVersion > APILEVEL::MASTER){
		LOGSYSTEM->Error(file + " is Newer than Game API:" + Functions::ToString(this->APIVersion) + ">" + Functions::ToString(APILEVEL::MASTER));
		this->fileOK = false;
		return;
	}

	this->baseGame = reader->ReadShort();
	FileTypes::eFileType fileType = static_cast<FileTypes::eFileType>(reader->ReadShort());

	this->DoFileType(fileType, reader);

	if(reader->EndOfFile() == false){
		this->LoadImagesFromFile(reader);
	}
	delete reader;
}

void OSData::File::LoadImagesFromFile(Functions::DataReader* reader){
	//READ IMAGES FROM END OF FILE
	unsigned int count = reader->ReadInt();

	if (count > 0){
		this->images = new std::vector<Functions::RGBImage*>();
		unsigned short width, height;
		for (unsigned int i = 0; i < count; i++){
			width = reader->ReadShort();
			height = reader->ReadShort();
			unsigned int size = width * height;
			RGBA* imageData = new RGBA[size];
			for (unsigned int j = 0; j < (size); j++){
				imageData[j] = reader->ReadInt();
			}

			Functions::RGBImage* image = new Functions::RGBImage(imageData,width,height);
			this->images->push_back(image);
		}
		if(this->dataType->LinkNumbers(this->images) == false)
			LOGSYSTEM->Error("PROBLEM WITH IMAGE LINKING");
	}
}

void OSData::File::ConstructFromXMLFile(std::string file){
	xmlDoc* xmlFile;
	xmlNode* rootNode;

	xmlFile = xmlReadFile(file.c_str(),NULL,XML_PARSE_NOBLANKS);
	rootNode = xmlDocGetRootElement(xmlFile);
	std::string rootNodeName = ((char *)rootNode->name);
	if (rootNodeName != "OpenSettlers"){
		LOGSYSTEM->Error("Root Node Not 'OpenSettlers':" + rootNodeName);
		this->fileOK = false;
		return;
	}
	FileTypes::eFileType fileType = FileTypes::eNone;
	xmlAttr* xmlAttribute = rootNode->properties;
	//ATTRIBUTES OF OPENSETTLERS TAB
	while(xmlAttribute){
		std::string xmlAttributeName = ((char*)xmlAttribute->name);
		std::string xmlAttributeValue = ((char*)xmlAttribute->children->content);
		if (xmlAttributeName ==  "BaseGame")
			this->baseGame = atoi(xmlAttributeValue.c_str());
		else if (xmlAttributeName ==  "FileType")
			this->GetFileType(xmlAttributeValue);

		xmlAttribute = xmlAttribute->next;
	}

	if(rootNode->children != NULL){

		if(fileType == FileTypes::eNone){
			fileType = this->GetFileType((char*)rootNode->children->name);
		}
		this->DoFileType(fileType, rootNode->children,true);

	}

	xmlFreeDoc(xmlFile);
	xmlCleanupParser();
}

OSData::FileTypes::eFileType OSData::File::GetFileType(std::string data){
	if (data == "Full")
		return FileTypes::eFull;
	else if (data == "Archive")
		return FileTypes::eArchive;
	else if (data == "MenuLayout")
		return FileTypes::eMenuLayout;
	else if (data == "LoadScreen")
		return FileTypes::eLoadScreen;

	return FileTypes::eNone;
}

void OSData::File::DoFileType(FileTypes::eFileType fileType,void* data, bool xml){

	switch(fileType){
	case FileTypes::eFull:
		if(xml)
			this->dataType = new GameType((xmlNode*)data);
		else
			this->dataType = new GameType((Functions::DataReader*)data);
		break;
	case FileTypes::eArchive:
		break;
	case FileTypes::eMenuLayout:
		if(xml)
			this->dataType = new MenuLayout((xmlNode*)data);
		else
			this->dataType = new MenuLayout((Functions::DataReader*)data);
		break;
	case FileTypes::eLoadScreen:
		break;
	default:
		break;
	}
}


OSData::File::~File() {
	if(keepData == true){
		if(this->images != NULL){
			delete this->images;
		}
	} else{
		if(this->dataType != NULL){
			delete this->dataType;
		}
		if(this->images != NULL){
			for(auto item = this->images->begin(); item != this->images->end(); item++) {
				delete (*item);
			}
			delete this->images;
		}
	}
}

bool OSData::File::ImageLocationsToNumbers(){
	if (this->images == NULL)
		this->images = new std::vector<Functions::RGBImage*>();
	if (this->imageLocations == NULL)
			this->imageLocations = new std::vector<std::string>();
	if (this->dataType != NULL)
		this->imagesAreNumbers = this->dataType->ImageToNumbers(this->images,this->imageLocations);

	for(auto item = this->images->begin(); item != this->images->end(); item++) {
		(*item)->FlipVertical();
	}

	return this->imagesAreNumbers;
}

bool OSData::File::ImageDataToNumbers(){
	if (this->images == NULL)
		this->images = new std::vector<Functions::RGBImage*>();
	if (this->dataType != NULL)
		this->imagesAreNumbers = this->dataType->ImageToNumbers(this->images);

	return this->imagesAreNumbers;
}

bool OSData::File::ToSaveToData(std::string file){
	if(this->fileOK == false) return false;

	std::vector<char>* data = new std::vector<char>();

	//Header 0x4f534554
	data->push_back('O');
	data->push_back('S');
	data->push_back('E');
	data->push_back('T');

	//Main API (INT)
	data->push_back(this->APIVersion & 0xFF);
	data->push_back((this->APIVersion >> 8) & 0xFF);
	data->push_back((this->APIVersion >> 16) & 0xFF);
	data->push_back((this->APIVersion >> 24) & 0xFF);

	//Base Game Number (Short)
	data->push_back(this->baseGame & 0xFF);
	data->push_back((this->baseGame >> 8) & 0xFF);

	//Data
	if (this->dataType->ToSaveToData(data) == false) return false;

	if (this->imagesAreNumbers){
		if(this->SaveImagesToData(data) == false) return false;
	}

	file.append(".dat");
	//Save to File
	Functions::SaveToBinaryFile(file,(char*)&*data->begin(),data->size());

	return true;
}

bool OSData::File::SaveImagesToData(std::vector<char>* data){
	if (this->images == NULL) return false;

	unsigned int count = this->images->size();
	data->push_back(count & 0xFF);
	data->push_back((count >> 8) & 0xFF);
	data->push_back((count >> 16) & 0xFF);
	data->push_back((count >> 24) & 0xFF);

	for(auto item = this->images->begin(); item != this->images->end(); item++) {
		unsigned short width = (*item)->Width();
		unsigned short height = (*item)->Height();
		unsigned int size = width*height;
		RGBA* imageData = (*item)->ImageRGBA();

		data->push_back(width & 0xFF);
		data->push_back((width >> 8) & 0xFF);

		data->push_back(height & 0xFF);
		data->push_back((height >> 8) & 0xFF);

		for(unsigned int i = 0; i < size; i++){
			data->push_back(imageData[i].A);
			data->push_back(imageData[i].B);
			data->push_back(imageData[i].G);
			data->push_back(imageData[i].R);
		}
	}
	return true;
}

std::string OSData::File::ToString(){
	std::string data;
	data += "Master API Level:" + Functions::ToString(this->APIVersion) + "\n";
	data += "BaseGame:" + Functions::ToString(this->baseGame) + "\n";

	if(this->dataType != NULL)
		data += this->dataType->ToString();

	if(this->images != NULL){
		data += "IMAGES IN BACK OF FILE:" + Functions::ToString(this->images->size()) + "\n";
	}
	return data;

}

OSData::MenuLayout* OSData::File::ReturnMenuLayout(){
	if (this->dataType->FileType() == FileTypes::eMenuLayout){
		return (MenuLayout*) this->dataType;
	}
	return NULL;
}

OSData::GameType* OSData::File::ReturnGameType(){
	if (this->dataType->FileType() == FileTypes::eFull){
		return (GameType*) this->dataType;
	}
	return NULL;
}

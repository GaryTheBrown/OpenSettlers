/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
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
	}

	size_t locationofdot = file.find_last_of(".");
	std::string extension = file.substr(locationofdot + 1);

	if (extension == "OSET"){
		this->ConstructFromDataFile(file);
	}else if (extension == "xml"){
		this->ConstructFromXMLFile(file);
	}
}

void OSData::File::ConstructFromDataFile(std::string file){

	Functions::DataReader* reader = new Functions::DataReader(file);

	unsigned int headCode = reader->ReadInt();

	//Make sure file is for Settlers 3
	if (headCode != 0x4f534554){ //"OSET"
		LOGSYSTEM->Error(file + "is not an Open Settlers File.");
		this->fileOK = false;
		return;
	}
	this->APIVersion = reader->ReadInt();
	if (this->APIVersion > APILEVEL::MASTER){
		LOGSYSTEM->Error(file + "is Newer than Game API:" + Functions::ToString(this->APIVersion) + ">" + Functions::ToString(APILEVEL::MASTER));
		this->fileOK = false;
		return;
	}

	this->baseGame = reader->ReadShort();

	FileTypes::eFileType fileType = static_cast<FileTypes::eFileType>(reader->ReadShort());

	switch(fileType){
	case FileTypes::eFull:
		break;
	case FileTypes::eArchive:
		break;
	case FileTypes::eMenuLayout:
		this->dataType = new MenuLayout(reader);
		break;
	case FileTypes::eLoadScreen:
		break;
	}

	delete reader;
}
void OSData::File::ConstructFromXMLFile(std::string file){
	xmlDoc* xmlFile;
	xmlNode* rootNode;

	xmlFile = xmlReadFile(file.c_str(),NULL,0);
	rootNode = xmlDocGetRootElement(xmlFile);

	if (rootNode->name != (const xmlChar *)"OpenSettlers"){
		LOGSYSTEM->Error("Root Node Not 'OpenSettlers'");
		this->fileOK = false;
		return;
	}

	xmlAttr* attribute = rootNode->properties;

	//TODO get baseGame number from within the node is this bellow it?
	while(attribute){
		if (attribute->name == (const xmlChar *)"BaseGame"){
			this->baseGame = atoi((char *)attribute->children->content);
		}

		attribute = attribute->next;
	}

	xmlFreeDoc(xmlFile);
	xmlCleanupParser();
}


OSData::File::~File() {
	if(this->dataType != NULL){
		delete this->dataType;
	}
}

bool OSData::File::ToSaveToData(std::string file){
	if(this->fileOK == false) return false;

	std::vector<char>* data = new std::vector<char>;

	//Header
	data->push_back('O');
	data->push_back('S');
	data->push_back('D');
	data->push_back('T');

	//Main API (INT)
	data->push_back((this->APIVersion >> 24) & 0xFF);
	data->push_back((this->APIVersion >> 16) & 0xFF);
	data->push_back((this->APIVersion >> 8) & 0xFF);
	data->push_back(this->APIVersion & 0xFF);

	//Base Game Number (Short)
	data->push_back((this->baseGame >> 8) & 0xFF);
	data->push_back(this->baseGame & 0xFF);

	//Data
	this->dataType->ToSaveToData(data);

	//Save to File
	Functions::SaveToBinaryFile(file,(char*)&data[0],data->size());

	return true;
}


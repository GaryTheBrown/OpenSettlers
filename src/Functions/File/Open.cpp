/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "Open.h"

Functions::File::File(std::string file){
	//- save Filename
	this->file = file;
	size_t lastindex = this->file.find_last_of(".");
	if (lastindex == std::string::npos)
		this->fileName = this->file;
	else{
		std::string tmpFileName = file.substr(0, lastindex);
		this->fileExt = file.substr(lastindex);
		lastindex = this->file.find_last_of("/");
		if (lastindex == std::string::npos)
			this->fileName = tmpFileName;
		else
			this->fileName = tmpFileName.substr(lastindex+1);
	}

	//Linux Space FIX
	//this->file.replace(this->file.find(" "),1,"\ ");

	//Windows Directory FIX
	//this->file.replace(this->file.find("\"),1,"\\");

	std::ifstream File(this->file, std::ios::in |std::ios::binary);

	//- get stream size
	File.seekg(0, File.end);
	this->fileSize = (unsigned int)File.tellg();
	File.seekg(0, File.beg);

	//- read file to buffer
	this->fileBuffer = new char[this->fileSize];
	File.read(this->fileBuffer, this->fileSize);

	File.close();

}

Functions::File::~File(){
	if (this->fileBuffer != NULL)
		delete[] this->fileBuffer;
}

const char* Functions::File::FetchBuffer(unsigned int offset,unsigned int size){
	int buffSize = 4;
	if (size > 4) buffSize = size;

	this->tmpBuffer = new char[buffSize];
	unsigned int count = 0;
	for (unsigned int i = offset; i < (offset+size); i++){
		this->tmpBuffer[count] = this->fileBuffer[i];
		count++;
	}
	return this->tmpBuffer;
}

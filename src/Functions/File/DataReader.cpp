/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "DataReader.h"

Functions::DataReader::DataReader(std::string filename, int hiddenOffset, int blockLength)
	:file(new File(filename)),
	hiddenOffset(hiddenOffset),
	blockLength(blockLength),
	endOfFile(true){

	if (this->blockLength > this->file->FileSize()) this->blockLength = file->FileSize();
	if (this->file->FileSize() > 0){
		this->endOfFile = false;
		if (blockLength >= 0)
			this->blockLength = blockLength;
		else
			this->blockLength = file->FileSize();
	}
	else{
		this->endOfFile = true;
		this->blockLength = 0;
	}
}

bool Functions::DataReader::SetOffset(unsigned int newOffset){
	this->offset = newOffset;
	this->endOfFile = (this->offset>this->blockLength);
	return this->endOfFile;
}
bool Functions::DataReader::MoveOffset(signed int value){
	this->offset += value;
	this->endOfFile = (this->offset>this->blockLength);
	return this->endOfFile;
}

char* Functions::DataReader::DirectBufferAccess(unsigned int size, int offset){
	if (size < 0)  return NULL;
	if (offset==-1) offset=this->offset;
	if (offset < 0) return NULL;
	if (this->blockLength < size + offset) return NULL;

	return (char *)this->file->readBuffer(this->hiddenOffset + offset);
}

const char* Functions::DataReader::FetchBuffer(int size){
	const char* out = NULL;
	if (size == -1) size = this->blockLength - this->offset;
	if (size < 0) size = 0;
	int ofs = this->hiddenOffset + this->offset;

	//- not EOF?
	if (this->offset<this->blockLength){
		//- requested size is available?
		if (this->offset + size > this->blockLength){
			this->endOfFile = true;
			size = this->blockLength - this->offset;
		}
		out = this->file->FetchBuffer(ofs,size);
	}
	else{
		this->endOfFile = true;
		out = NULL;
	}
	this->offset += size;
	return out;
}

unsigned char Functions::DataReader::ReadChar(){
	unsigned char returnVal = 0;
	const char* tmp = this->FetchBuffer(1);
	if (tmp != NULL){
		returnVal = (unsigned char) *tmp;
	}
	delete [] tmp;
	if(this->bigEndian) this->endswap(&returnVal);
	return returnVal;
}
unsigned short Functions::DataReader::ReadShort(){
	unsigned short returnVal = 0;
	const char* tmp = this->FetchBuffer(2);
	if (tmp != NULL){
		returnVal = (unsigned short)((*((int*) tmp)) & 0x0000FFFF);
	}
	delete [] tmp;
	if(this->bigEndian) this->endswap(&returnVal);
	return returnVal;
}

unsigned int Functions::DataReader::ReadInt(){
	unsigned int returnVal = 0;
	const char* tmp = this->FetchBuffer(4);
	if (tmp != NULL){
		returnVal = *((unsigned int*)tmp);
	}
	delete [] tmp;
	if(this->bigEndian) this->endswap(&returnVal);
	return returnVal;
}

unsigned long long Functions::DataReader::ReadLongLong(){
	unsigned long long returnVal = 0;
	const char* tmp = this->FetchBuffer(8);
	if (tmp != NULL){
		returnVal = *((unsigned long long*)tmp);
	}
	delete [] tmp;
	if(this->bigEndian) this->endswap(&returnVal);
	return returnVal;
}

signed short Functions::DataReader::ReadSignedShort(){
	signed short returnVal = 0;
	const char* tmp = this->FetchBuffer(2);
	if (tmp != NULL){
		returnVal = (signed short)((*((int*) tmp)) & 0x0000FFFF);
	}
	delete [] tmp;
	if(this->bigEndian) this->endswap(&returnVal);
	return returnVal;
}

std::string Functions::DataReader::ReadString(int size, unsigned int offset){

	if (size == -1) size = this->blockLength - offset;
	if (size < 0) size = 0;

	int ofs = this->hiddenOffset + offset;

	//- not EOF?
	if (offset<this->blockLength){
		//- requestet size is available?
		if (offset + size>this->blockLength){
			this->endOfFile = true;
			size = this->blockLength - offset;
		}
		std::string out(this->file->FetchBuffer(ofs,size));
		return out;
	}
	else{
		this->endOfFile = true;
		size = 0;
		return "";
	}
}
std::string Functions::DataReader::ReadString(unsigned int size){
	char* text = new char[size];
	for (unsigned char i = 0; i < size; i++){
		text[i] = this->ReadChar();
	}
	std::string returnString(text,size);
	delete text;
	return returnString;
}

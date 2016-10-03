/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Run.h"


std::string Functions::ExternalProgram::Run(std::string program, std::string arguments,bool show){

	std::string command = program + " " + arguments;
	FILE* pipe = popen(command.c_str(), "r");

	char buffer[128];
	std::string result = "";
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
		if(result != "")
			if (show) LOGSYSTEM->Log(buffer,2,false);
	}
	pclose(pipe);
	return result;

}

bool Functions::ExternalProgram::GOGExtract(){
	if (access(this->innoextract.c_str(), X_OK) == 0) {
		LOGSYSTEM->Log("Running innoextract...",1);
		std::string error = this->Run(this->innoextract,this->innoextractArgumentsExtract + " " + this->location);
		if (error.length() < 100){
			LOGSYSTEM->Error("GOG Extraction FAILED!: innoextract error!");
			LOGSYSTEM->Error(error);
			return false;
		}
		LOGSYSTEM->Log("innoextract complete ",1);
		return true;
	}else
		LOGSYSTEM->Error("CAB Extraction FAILED! innoextract not found");
	return false;
}
std::string Functions::ExternalProgram::GOGGameCheck(){
	if (access(this->unshield.c_str(), X_OK) == 0){
		return this->Run(this->innoextract,this->innoextractArgumentsGameCheck + " " + this->location, false);
	}
	return "";
}

bool Functions::ExternalProgram::CABExtract(std::string file){
	if (access(this->unshield.c_str(), X_OK) == 0){
		LOGSYSTEM->Log("Running unshield...",1);
		std::string error = this->Run(this->unshield,this->unshieldArguments + " " + this->location + file);
		if (error.length() < 100){
			LOGSYSTEM->Error("CAB Extraction FAILED! unshield error");
			LOGSYSTEM->Error(error);
			return false;
		}
		LOGSYSTEM->Log("unshield Complete",1);
		return true;
	}else
		LOGSYSTEM->Error("CAB Extraction FAILED! unshield not found");
	return false;
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "LogSystem.h"

LogSystem::LogSystem(signed char verboseLevelCLI,signed char verboseLevelFile, signed char verboseLevelConsole)
	:verboseLevelCLI(verboseLevelCLI),
	verboseLevelFile(verboseLevelFile),
	verboseLevelConsole(verboseLevelConsole){
	logFile.open(this->logFileName.c_str(), std::ofstream::out);
	logFile.close();
}

std::string LogSystem::TimeToString(){
	std::string zero = "0";
	std::string blank = "";
	time_t t = time(0);
    struct tm * now = localtime( & t );
    std::string timeString = (now->tm_mday < 10?zero:blank) + Functions::ToString(now->tm_mday);
    timeString += "/" + (now->tm_mon < 10?zero:blank) + Functions::ToString(now->tm_mon + 1);
    timeString += '/' + Functions::ToString(now->tm_year + 1900);
    timeString += "-" + (now->tm_hour < 10?zero:blank) + Functions::ToString(now->tm_hour);
    timeString += ":" + (now->tm_min < 10?zero:blank) + Functions::ToString(now->tm_min);
	timeString += ":" + (now->tm_sec < 10?zero:blank) + Functions::ToString(now->tm_sec);

	return timeString;
}

void LogSystem::Out(std::string text, signed char verboseLevel){
	if(this->verboseLevelCLI >= verboseLevel){
		std::cout << text;
	}
	if(this->verboseLevelFile >= verboseLevel){
		logFile.open(this->logFileName.c_str(), std::ofstream::out | std::ofstream::app);
		logFile << text;
		logFile.close();
	}
}

void LogSystem::Log(std::string info, signed char verboseLevel, bool newLine){
	std::string text = this->TimeToString() + ":LOG(" + Functions::ToString((int)verboseLevel) + "):" + info;
	if (newLine) text += "\n";
	this->Out(text, verboseLevel);
}

void LogSystem::Message(std::string info, bool newLine){
	std::string text = this->TimeToString() + ":MESSAGE:" + info;
	if (newLine) text += "\n";
	this->Out(text);
}

void LogSystem::Error(std::string info){
	std::string text =  "\033[1;31m";// set cli colour to red.
	text += this->TimeToString() + ":ERROR:" + info + "\n";
	text += "\033[0m"; // reset cli colour to Normal
	this->Out(text);
}

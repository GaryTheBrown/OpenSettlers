/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#ifndef LOGSYSTEM_LOGSYSTEM_H_
#define LOGSYSTEM_LOGSYSTEM_H_

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include "../Functions/To.h"

class LogSystem {
private:

	signed char verboseLevelCLI;
	signed char verboseLevelFile = -1;
	signed char verboseLevelConsole = -1;//in game console
	//-1 = no info 0 = errors and messages only 127 = all info

	std::ofstream logFile;
	std::string logFileName = "SettlersExtractor.log";

	std::string TimeToString();
	void Out(std::string Text, signed char verboseLevel = 0);

public:
	LogSystem(signed char verboseLevelCLI, signed char verboseLevelFile = -1, signed char verboseLevelConsole = -1);
	virtual ~LogSystem();

	void Log(std::string info, signed char verboseLevel = 1, bool newLine = true);
	void Message(std::string info, bool newLine = true);
	void Error(std::string info);
	void LogCont(std::string info, signed char verboseLevel);
	void newLine(signed char verboseLevel);


};
#endif

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "Functions.h"

namespace Functions{
	bool FileExists(std::string file){
		std::ifstream ifile(file.c_str());
		if (ifile.is_open() == false)
			return false;
		ifile.close();
		return true;
	}

	bool FolderExists(std::string folder){
		struct stat info;
		if((stat(folder.c_str(), &info ) != 0)||!(info.st_mode & S_IFDIR))
			return false;
		return true;
	}

	void CreateDir(std::string FileName){
		if(FolderExists(FileName) == false){
			std::string command = "mkdir \"" + FileName + "\"";
			if(system(command.c_str()) == -1)
				return;
		}
	}

	void Copy(std::string from, std::string to){
	     std::ifstream source(from, std::ios::binary);
	     std::ofstream destination(to, std::ios::binary);
	     destination << source.rdbuf();
	}

	void RemoveFolder(std::string folder){
		std::string command;
		//LINUX ONLY
#ifdef __linux__
		command = "rm -r " + folder;
#elif _WIN32
		command = "rmdir /S /Q PATH";
#endif
		if(system(command.c_str()) == -1)
			return;
	}

	std::vector<std::string> GetDir(std::string directory){
		std::vector<std::string> outVector;
#ifdef _WIN32
	    HANDLE dir;
	    WIN32_FIND_DATA fileData;

	    if ((dir = FindFirstFile((directory + "/*").c_str(), &fileData)) == INVALID_HANDLE_VALUE)
	        return 0; /* No files found */
	    do {
	        if ((fileData.cFileName[0] == '.')||((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)) continue;
	        outVector.push_back(fileData.cFileName);
	    } while (FindNextFile(dir, &fileData));

	    FindClose(dir);
#else
	    DIR *dir;
	    class dirent *ent;
	    class stat st;

	    dir = opendir(directory.c_str());
	    while ((ent = readdir(dir)) != NULL) {
	        if ((ent->d_name[0] == '.')||(stat((directory + "/" + ent->d_name).c_str(), &st) == -1)||((st.st_mode & S_IFDIR) != 0)) continue;
	        outVector.push_back(ent->d_name);
	    }
	    closedir(dir);
#endif
	    return outVector;
	}
}

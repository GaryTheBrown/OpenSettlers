/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Functions.h"

bool Functions::FileExists(std::string file){
	std::ifstream ifile(file.c_str());
	if (ifile.is_open() == false)
		return false;
	ifile.close();
	return true;
}

bool Functions::FolderExists(std::string folder){
	struct stat info;
	if((stat(folder.c_str(), &info ) != 0)||!(info.st_mode & S_IFDIR))
		return false;
	return true;
}

void Functions::CreateDir(std::string FileName){
	if(FolderExists(FileName) == false){
		std::string command = "mkdir \"" + FileName + "\"";
		if(system(command.c_str()) == -1)
			return;
	}
}

void Functions::Copy(std::string from, std::string to){
	std::ifstream source(from, std::ios::binary);
	std::ofstream destination(to, std::ios::binary);
	destination << source.rdbuf();
}

void Functions::RemoveFolder(std::string folder){
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

std::vector<std::string>* Functions::GetFilesInDirectory(std::string directory){
	std::vector<std::string>* outVector = new std::vector<std::string>();
#ifdef _WIN32
	HANDLE dir;
	WIN32_FIND_DATA fileData;

	if ((dir = FindFirstFile((directory + "/*").c_str(), &fileData)) == INVALID_HANDLE_VALUE){
		delete outVector;
		return 0; /* No files found */
	}
	do {
		if ((fileData.cFileName[0] == '.')||((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)) continue;
		outVector->push_back(fileData.cFileName);
	} while (FindNextFile(dir, &fileData));

	FindClose(dir);
#else
	DIR *dir;
	class dirent *ent;
	class stat st;

	dir = opendir(directory.c_str());
	while ((ent = readdir(dir)) != NULL) {
		if ((ent->d_name[0] == '.')||(stat((directory + "/" + ent->d_name).c_str(), &st) == -1)||((st.st_mode & S_IFDIR) != 0)) continue;
		outVector->push_back(ent->d_name);
	}
	closedir(dir);
#endif
	std::sort(outVector->begin(),outVector->end());
	return outVector;
}

std::vector<std::string>* Functions::GetFoldersInDirectory(std::string directory, bool showDir){
	std::vector<std::string>* outVector = new std::vector<std::string>();
#ifdef _WIN32
	HANDLE dir;
	WIN32_FIND_DATA fileData;

	if ((dir = FindFirstFile((directory + "/*").c_str(), &fileData)) == INVALID_HANDLE_VALUE){
		delete outVector;
		return 0; /* No files found */
	}
	do {
		if ((fileData.cFileName[0] == '.') != 0) continue;
		outVector->push_back(fileData.cFileName + (showDir?"/":""));
	} while (FindNextFile(dir, &fileData));

	FindClose(dir);
#else
	DIR *dir = opendir(directory.c_str());
	struct dirent *entry = readdir(dir);
	while (entry != NULL){
		if (entry->d_type == DT_DIR){
			if(entry->d_name[0] != '.'){
				outVector->push_back(std::string(entry->d_name) + (showDir?"/":""));
			}
		}
		entry = readdir(dir);
	}
#endif
	closedir(dir);
	std::sort(outVector->begin(),outVector->end());
	return outVector;
}

std::vector<std::string>* Functions::GetFullDirectory(std::string directory){
	std::vector<std::string>* directories = GetFoldersInDirectory(directory,true);
	std::vector<std::string>* files = GetFilesInDirectory(directory);
	directories->insert(directories->end(), files->begin(), files->end());
	return directories;
}

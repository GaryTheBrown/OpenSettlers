/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Extractor.h"
namespace Extractor{
	namespace Settlers2{
		Extract::Extract(std::string location,bool GOG){
			this->location = location;
			this->CheckGameVersion(GOG);
		}

		Extract::~Extract(){
			if(Functions::FolderExists("app")){
				LOGSYSTEM->Log("Cleaning up Extracted GOG Data",1);
				Functions::RemoveFolder("app");
				Functions::RemoveFolder("sys");
				Functions::RemoveFolder("tmp");
				if(Functions::FolderExists("commonappdata")) Functions::RemoveFolder("commonappdata");
			}
		}

		void Extract::CheckGameVersion(bool GOG){
			//GOG INSTALLERS.
			if(GOG){
				LOGSYSTEM->Message("Detected Settlers 2 GOG Installer");
				this->gameVersion = VersionS2GOG;
			}
			//INSTALLED
			else if(Functions::FileExists(this->location + "S2.EXE")){
				if(Functions::FileExists(this->location + "S2EDIT.EXE")){
					if(Functions::FileExists(this->location + "INSTALL.OLD")){
						LOGSYSTEM->Message("Detected Settlers 2 Mission CD Installed Version");
						this->gameVersion = VersionS2MCDINSTALL;
					}else{
						if(Functions::FileExists(this->location + "goggame.dll")){
							LOGSYSTEM->Message("Detected Settlers 2 GOG Installed Version");
							this->gameVersion = VersionS2GOGINSTALL;
						}else{
							LOGSYSTEM->Message("Detected Settlers 2 GOLD Installed Version");
							this->gameVersion = VersionS2GOLDINSTALL;
						}
					}
				}else{
					LOGSYSTEM->Message("Detected Settlers 2 Installed Version");
					this->gameVersion = VersionS2DISCINSTALL;
				}
			}
			//DISCS
			else if(Functions::FileExists(this->location + "autorun.exe")){
				if(Functions::FileExists(this->location + "readme.txt")){
					LOGSYSTEM->Message("Detected Settlers 2 Mission CD");
					this->gameVersion = VersionS2MCD;
				}else if(Functions::FileExists(this->location + "world.txt")){
					LOGSYSTEM->Message("Detected Settlers 2 GOLD CD");
					this->gameVersion = VersionS2GOLD;
				}else{
					LOGSYSTEM->Message("Detected Settlers 2 CD");
					this->gameVersion = VersionS2CD;
				}
			}else{
				LOGSYSTEM->Error("Detection of Version Failed");
				this->gameVersion = VersionNONE;
			}
		}

		bool Extract::FullRAWExtract(){
			if(this->gameVersion == VersionNONE) return false;
			Functions::CreateDir("Extracted");
			Functions::CreateDir("Extracted/S2");


			//Functions::CreateDir("Extracted/S2/GFX/");
			//Functions::CreateDir("Extracted/S2/SND/");
			//Functions::CreateDir("Extracted/S2/MAP/");

			if(this->gameVersion == VersionS2CD){//Original CD
				LOGSYSTEM->Log("Settlers 2 Original CD",1);
			}else if(this->gameVersion == (VersionS2GOLD)){//GOLD CD
				LOGSYSTEM->Log("Settlers 2 Gold CD",1);
			}else if(this->gameVersion == VersionS2MCD){//MISSION CD
				LOGSYSTEM->Log("Settlers 2 Mission CD",1);
			} else if(this->gameVersion == (VersionS2GOG)){//GOG not installed
				Functions::ExternalProgram* program = new Functions::ExternalProgram(this->location);
				if(Functions::FolderExists("app") == false){
					if(program->GOGExtract() == false) return false;
				}else
					LOGSYSTEM->Log("GOG Extract: Already Extracted",1);
				delete program;
			} else if(this->gameVersion == (VersionS2GOGINSTALL)){//GOG installed

			} else if(this->gameVersion == (VersionS2DISCINSTALL)){//Disc installed

			} else if(this->gameVersion == (VersionS2MCDINSTALL)){//MCD installed

			} else if(this->gameVersion == (VersionS2GOLDINSTALL)){//GOLD installed

			} else{
				LOGSYSTEM->Error("Detection of Settlers 2 version failed");
				return false;
			}
			return true;
		}

		bool Extract::RAWLBMFileExtract(std::string folder, std::string file){
			if(Functions::FileExists(folder+file)){
				LOGSYSTEM->Log("Open GFX Data File: "+ file,1);
				LOGSYSTEM->Log("Extracting...",1);
				LBMDataType* LBMFile = new LBMDataType(folder+file);
				LOGSYSTEM->Log("Saving...",1);
				Functions::CreateDir("Extracted/");
				Functions::CreateDir("Extracted/S2/");
				Functions::CreateDir("Extracted/S2/LBM/");
				Functions::CreateDir("Extracted/S2/LBM/"+ file);
				//LBMFile->SaveFileData("Extracted/S2/LBM/" + file);
				LOGSYSTEM->Log("Closing...",1);
				delete LBMFile;
				return true;
			}else return false;
		}

		void Extract::RAWLBMFolderExtract(std::string folder){
			if(Functions::FolderExists(folder)){
				std::vector<std::string> fileList = Functions::GetDir(folder);
				for(unsigned int i=0; i < fileList.size(); i++){
					this->RAWLBMFileExtract(folder,fileList[i]);
				}
			}
		}

		bool Extract::ManualExtract(eType fileType, std::string location){
			size_t pos = location.find_last_of("/");
			if(pos != location.length()-1){
				std::string file = location.substr(pos+1);
				std::string folder = location.substr(0,pos+1);

				switch(fileType){//File
					case LBM:
						this->RAWLBMFileExtract(folder,file);
						break;
					default:
						return false;
				}

			}else{
				switch(fileType){//Folder
					case LBM:
						this->RAWLBMFolderExtract(location);
						break;
					default:
						return false;
				}
			}
			return true;
		}
	}
}

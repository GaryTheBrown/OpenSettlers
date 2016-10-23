/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Extractor.h"

bool Extractor::Main(std::string location){
	eType fileType = FULL;
	char gameNo = 0;
	bool GOG = false;

	//First check if location is a file (with extension)
	size_t locationofdot = location.find_last_of(".");
	std::string extension = location.substr(locationofdot + 1);
	std::string fileWithoutExtension = location.substr(0, locationofdot);
	std::transform(extension.begin(), extension.end(), extension.begin(), toupper);
	if ((locationofdot != std::string::npos)&&(extension.length() == 3)){//File with 3 letter extension name
		//Settlers 2 File Types
		if (extension == "LBM"){
			fileType = LBM;
			gameNo = 2;
			LOGSYSTEM->Log("LBM File Type",1);
		}
		if (extension == "BBM"){
			fileType = BBM;
			gameNo = 2;
			LOGSYSTEM->Log("BBM File Type",1);
		}
		if (extension == "LST"){
			fileType = LST;
			gameNo = 2;
			LOGSYSTEM->Log("LST File Type",1);
		}
		else if (extension == "IDX") {
			if (Functions::FileExists(fileWithoutExtension + ".DAT")){
			fileType = IDX;
			gameNo = 2;
			}else{
				LOGSYSTEM->Error("IDX file without DAT File");
				fileType = SKIP;
				gameNo = 2;
			}
		}
		if (extension == "BOB"){
			fileType = BOB;
			gameNo = 2;
			LOGSYSTEM->Log("BOB File Type",1);
		}
		//Settlers 3 File Types
		else if (extension == "MAP"){
			fileType = MAP;
			gameNo = 3;
		}
		//MULTI GAME File Types
		else if (extension == "DAT") {
			LOGSYSTEM->Log("Reading DAT File Type",1);
			if (Functions::FileExists(fileWithoutExtension + ".IDX")){
				fileType = SKIP;
				gameNo = 2;
			}else{
				Functions::DataReader *reader = new Functions::DataReader(location);
				int code = reader->ReadInt();
				delete reader;
				switch(code){
				case 267012: //GFX
					fileType = GFX;
					gameNo = 3;
					break;
				case 70980: //SND
					fileType = SND;
					gameNo = 3;
					break;
				case 9460301: // GFX S3_18.DAT is a DOS DLL file
					LOGSYSTEM->Log("S3_18.DAT Detected Nothing to do.",1);
					return true;
				case 1179011410: //VIDEO
					LOGSYSTEM->Log("Video File Detected Nothing to do.",1);
					return true;
				default:
					LOGSYSTEM->Log("File Not Recognised",1);
					return true;
				}
			}
		}
		//GOG EXE's
		else if (extension == "EXE"){
			if ((gameNo != 2)&&(gameNo != 3)&&(gameNo != 4)){
				LOGSYSTEM->Log("Reading GOG EXE File",1);

				Functions::ExternalProgram* program = new Functions::ExternalProgram(location);
				std::string returnstring = program->GOGGameCheck();

				int spos = returnstring.find("\"") + 1;
				int epos = returnstring.find_last_of("\"");

				std::string gameName = returnstring.substr(spos, (epos - spos));

				if (gameName == "Settlers 2 GOLD"){
					gameNo = 2;
				}else if (gameName == "The Settlers 3 - Ultimate Collection"){
					gameNo = 3;
				}else if (gameName == "The Settlers IV GOLD"){
					gameNo = 4;
				}
				delete program;
			}
			GOG = true;
		}
	}
	//If not a file then treat as a folder
	else{
		size_t pos = location.find_last_of("/");
		if(pos != location.length()-1) location += "/";

		if(gameNo == 0){
			LOGSYSTEM->Log("Reading Location:"+location,1);
			//if Settlers 1
			if(Functions::FileExists(location + "SETTLER.BAT")){
				gameNo = 1;
			}
			//if Settlers 2
			else if((Functions::FolderExists(location + "s2"))||
					(Functions::FileExists(location + "S2.EXE"))){
				gameNo = 2;
			}
			//if Settlers 3
			else if((Functions::FolderExists(location + "s3"))||(Functions::FileExists(location + "s3.exe"))
					||(Functions::FileExists(location + "S3.EXE"))||(Functions::FolderExists(location + "s3update"))
					||(Functions::FolderExists(location + "S3UPDATE"))){
				gameNo = 3;
			}
			//if Settlers 4
			else if((Functions::FolderExists(location + "s4"))||(Functions::FolderExists(location + "S4"))
					||(Functions::FileExists(location + "s4.exe"))||(Functions::FileExists(location + "S4.exe"))
					||(Functions::FileExists(location + "S4_Main.exe"))){
				gameNo = 4;
			}
			else{//Not a Game Folder so scan and run this function on each file.
				LOGSYSTEM->Log("No Game Detected Getting Directory List and checking each file.",1);
				std::vector<std::string>* fileList = Functions::GetFilesInDirectory(location);

				for(unsigned int i=0; i < fileList->size(); i++){
					LOGSYSTEM->Log("FILE:" + fileList->at(i),1);
					if (Main(location + fileList->at(i))== false) return false;
				}
				return true;
			}

		}
	}
	//Make sure a Game Number has been selected
	if ((gameNo == 0)||(gameNo >= 5)){
		LOGSYSTEM->Error("Game Number Not found");
		return false;
	}

	switch(fileType){
	case SKIP:{//This is to allow the skipping of a file if the file is a paired file (Settlers 2 IDX & DAT)
		return true;
	}
	case FULL:{
		switch(gameNo){
		case 1:{
			//temp message of version
			LOGSYSTEM->Log("Settlers 1 Detected.",1);
			LOGSYSTEM->Error("Settlers 1 not implemented yet.");
			return false;
		}
		case 2:{
			Settlers2::Extract* s2Extract = new Settlers2::Extract(location,GOG);
			if(s2Extract->FullRAWExtract() == false) return false;
			delete s2Extract;
			return true;
		}
		case 3:{
			Settlers3::Extract* s3Extract = new Settlers3::Extract(location,GOG);
			if(s3Extract->FullRAWExtract() == false) return false;
			delete s3Extract;
			return true;
		}
		case 4:{
			//temp message of version
			if(GOG)
				LOGSYSTEM->Log("Settlers 4 GOG Detected.",1);
			else
				LOGSYSTEM->Log("Settlers 4 Detected.",1);

			LOGSYSTEM->Error("Settlers 4 not implemented yet.");
			break;
		}
		default:{
			// If nothing above found then
			LOGSYSTEM->Error("No game Detected.");
			break;
		}
		}
		return false;
	}
	case LBM:
	case BBM:
	case LST:
	case IDX:
	case BOB:{
		Settlers2::Extract* s2Extract = new Settlers2::Extract();
		if(s2Extract->ManualExtract(fileType, location) == false) return false;
		delete s2Extract;
		return true;
	}
	case GFX:
	case SND:
	case MAP:{
		Settlers3::Extract* s3Extract = new Settlers3::Extract();
		if(s3Extract->ManualExtract(fileType, location) == false) return false;
		delete s3Extract;
		return true;
	}

	default:
		LOGSYSTEM->Error("UNKNOWN OPTION HOW DID THIS APPEAR?");
		return false;
	}
	return true;
}


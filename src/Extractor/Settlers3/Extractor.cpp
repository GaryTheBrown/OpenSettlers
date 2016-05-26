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
	namespace Settlers3{
		Extract::Extract(std::string location,bool GOG){
			this->location = location;
			//------------------//
			//Game Version Check//
			//------------------//

			//GOG INSTALLERS.
			if(GOG){
				LOGSYSTEM->Message("Detected Settlers 3 GOG Installer");
				this->gameVersion = VersionS3GOG;
			}
			//DISC INSTALLED
			else if(Functions::FileExists(this->location + "s3.exe")){
				if(Functions::FolderExists(this->location + "EXTRAS")){
					LOGSYSTEM->Message("Detected Settlers 3 GOLD Installed Version");
					this->gameVersion = VersionS3GOLDINSTALL;
				}else{
					LOGSYSTEM->Message("Detected Settlers 3 Installed Version");
					this->gameVersion = VersionS3DISCINSTALL;
				}
			}

			//GOG INSTALLED
			else if(Functions::FileExists(this->location + "S3.EXE")){
				LOGSYSTEM->Message("Detected Settlers 3 GOG Installed Version");
				this->gameVersion = VersionS3GOGINSTALL;
			}
			//DISCS
			else if((Functions::FileExists(this->location + "S3GOLD1.DAT"))||(Functions::FileExists(this->location + "s3gold1.dat"))){
				LOGSYSTEM->Message("Detected Settlers 3 GOLD CD 1");
				this->gameVersion = VersionS3GOLD1;
			}
			else if((Functions::FileExists(this->location + "S3GOLD2.DAT"))||(Functions::FileExists(this->location + "s3gold2.dat"))){
				LOGSYSTEM->Message("Detected Settlers 3 GOLD CD 2");
				this->gameVersion = VersionS3GOLD2;
			}
			else if((Functions::FileExists(this->location + "S3CD1.DAT"  ))||(Functions::FileExists(this->location + "s3cd1.dat"  ))){
				LOGSYSTEM->Message("Detected Settlers 3 CD 1");
				this->gameVersion = VersionS3CD1;
			}
			else if((Functions::FileExists(this->location + "S3CD2.DAT"  ))||(Functions::FileExists(this->location + "s3cd2.dat"  ))){
				LOGSYSTEM->Message("Detected Settlers 3 CD 2");
				this->gameVersion = VersionS3CD2;
			}
			else if((Functions::FileExists(this->location + "S3MCD1.DAT" ))||(Functions::FileExists(this->location + "s3mcd1.dat" ))){
				LOGSYSTEM->Message("Detected Settlers 3 Mission CD");
				this->gameVersion = VersionS3MCD1;
			}
			else if((Functions::FileExists(this->location + "S3QOTA1.DAT"))||(Functions::FileExists(this->location + "s3qota1.dat"))){
				LOGSYSTEM->Message("Detected Settlers 3 Quest Of The Amazon CD");
				this->gameVersion = VersionS3QOTA1;
			}
			else{
				LOGSYSTEM->Error("Detection of Version Failed");
			}

		}

		Extract::~Extract(){
			if(Functions::FolderExists("EXE")){
				LOGSYSTEM->Log("Cleaning up Extracted Cab Data",1);
				Functions::RemoveFolder("EXE");
			}
			if(Functions::FolderExists("app")){
				LOGSYSTEM->Log("Cleaning up Extracted GOG Data",1);
				Functions::RemoveFolder("app");
				Functions::RemoveFolder("sys");
				Functions::RemoveFolder("tmp");
			}
		}

		bool Extract::RAWExtract(){
			std::string GFX = "";
			std::string SND = "";
			Functions::CreateDir("Extracted");
			Functions::CreateDir("Extracted/S3");
			Functions::CreateDir("Extracted/S3/GFX");
			if(this->gameVersion != VersionS3MCD1) Functions::CreateDir("Extracted/S3/SND");

			if(this->gameVersion == VersionS3CD2){//Original CD 2
				LOGSYSTEM->Message("Nothing to extract.(try Disc 1)");
				return false;
			}
			else if(this->gameVersion == (VersionS3GOLD1)){//GOLD CD 1
				LOGSYSTEM->Message("Nothing to extract.(try Disc 2)");
				return false;
			}
			else if(this->gameVersion == VersionS3MCD1){//MISSION CD
				//	s3update/s3_xx.dat : 07,08,09,60,99
				std::string fileNumbers[5] = {"07","08","09","60","99"};
				for(int i = 0; i < 5; i++){
					this->RAWGFXFileExtract(this->location + "s3update/","s3_" + fileNumbers[i] +".dat");
				}
				return true;
			}
			else if(this->gameVersion == VersionS3QOTA1){//QUEST OF THE AMAZON CD
				std::string fileNumbers[29] = {"01","03","06","07","08","09","11","12","13","14","15","21","25","27","30","31","33","35","36","40","41","42","43","44","45","46","47","48","99"};
				for(int i = 0; i < 29; i++){
					this->RAWGFXFileExtract(this->location + "S3UPDATE/","S3_" + fileNumbers[i] +".DAT");
				}

				this->RAWSNDFileExtract(this->location + "S3UPDATE/","SND3_00.DAT");
				return true;
			}

			else if(this->gameVersion == (VersionS3GOLD2)){//GOLD CD 2
				Functions::ExternalProgram* program = new Functions::ExternalProgram(this->location);
				if(Functions::FolderExists("EXE") == false){
					if(program->CABExtract("s3/install/data.cab") == false)
						return true;
				}else
					LOGSYSTEM->Log("CABExtract: Already Extracted",1);
				this->location = "EXE/";
				delete program;

				GFX = "GFX/";
				SND = "SND/";
			}
			else if(this->gameVersion == (VersionS3GOG)){//GOG not installed
				Functions::ExternalProgram* program = new Functions::ExternalProgram(this->location);
				if(Functions::FolderExists("app") == false){
					if(program->GOGExtract() == false)
						return true;
				}else
					LOGSYSTEM->Log("GOG Extract: Already Extracted",1);

				delete program;

				GFX = "GFX/";
				SND = "SND/";
				//Change Location of files.
				this->location = "app/";
			}
			else if(this->gameVersion == VersionS3CD1){//Original CD 1
				GFX = "s3/gfx/";
				SND = "s3/snd/";
			}
			else if(this->gameVersion == (VersionS3GOGINSTALL)){//GOG installed
				GFX = "GFX/";
				SND = "SND/";
			}
			else if(this->gameVersion == (VersionS3DISCINSTALL)){//Disc installed
				GFX = "Gfx/";
				SND = "Snd/";
			}
			else if(this->gameVersion == (VersionS3GOLDINSTALL)){//GOLD installed
				GFX = "GFX/";
				SND = "SND/";
			}
			else{
				LOGSYSTEM->Error("Detection of Settlers 3 version failed");
				return false;
			}
			this->RAWGFXFolderExtract(this->location + GFX);
			this->RAWSNDFolderExtract(this->location + SND);
			return true;
		}

		bool Extract::RAWGFXFileExtract(std::string folder, std::string file){
			if(Functions::FileExists(folder+file)){
				LOGSYSTEM->Log("Open GFX Data File: "+ file,1);
				LOGSYSTEM->Log("Extracting...",1);
				GFXDataType* GFXFile = new GFXDataType(folder+file);
				Functions::CreateDir("Extracted/S3/GFX/"+ file);
				LOGSYSTEM->Log("Saving...",1);
				GFXFile->SaveFileData("Extracted/S3/GFX/" + file);
				LOGSYSTEM->Log("Closing...",1);
				delete GFXFile;
				return true;
			}else return false;
		}

		bool Extract::RAWSNDFileExtract(std::string folder, std::string file){
			if(Functions::FileExists(folder+file)){
				LOGSYSTEM->Log("Open SND Data File: "+ file,1);
				LOGSYSTEM->Log("Extracting...",1);
				SNDDataType* SNDFile = new SNDDataType(folder+file);
				LOGSYSTEM->Log("Saving...",1);
				Functions::CreateDir("Extracted/S3/SND/"+ file);
				SNDFile->SaveFileData("Extracted/S3/SND/" + file);
				LOGSYSTEM->Log("Closing...",1);
				delete SNDFile;
				return true;
			}else return false;
		}

		void Extract::RAWGFXFolderExtract(std::string folder){
			std::string fileNameFront[5] = {"Siedler3_", "siedler3_", "s3_", "Siedler3_", "siedler3_"};
			std::string fileNameBack[5] = {".f8007e01f.dat", ".f8007e01f.dat", ".dat", ".7c003e01f.dat", ".7c003e01f.dat"};
			for(int i = 0; i < 99; i++){
				if (i == 18) i++;
				for(int j = 0; j < 5; j++){
					std::string file = fileNameFront[j];
					file += (i<10?"0":"");
					file += Functions::ToString(i);
					file += fileNameBack[j];
					if(this->RAWGFXFileExtract(folder,file)) break;
				}
			}
		}

		void Extract::RAWSNDFolderExtract(std::string folder){
			std::string fileNames[6] = {"Siedler3_00.dat", "siedler3_00.dat", "Siedler3_01.dat", "siedler3_01.dat", "s3_00.dat", "s3_01.dat"};
			for(int i = 0; i < 6; i++){
				this->RAWSNDFileExtract(folder,fileNames[i]);
			}
		}
	}
}

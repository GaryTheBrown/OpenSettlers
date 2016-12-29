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

Extractor::Settlers3::Extract::Extract(std::string location,bool GOG)
	:location(location){
	this->gameVersion = CheckGameVersion(location,GOG);
}

Extractor::Settlers3::Extract::~Extract(){
	if(Functions::FolderExists("EXE")){
		LOGSYSTEM->Log("Cleaning up Extracted Cab Data",1);
		Functions::RemoveFolder("EXE");
	}
	if(Functions::FolderExists("app")){
		LOGSYSTEM->Log("Cleaning up Extracted GOG Data",1);
		Functions::RemoveFolder("app");
		Functions::RemoveFolder("sys");
		Functions::RemoveFolder("tmp");
		if(Functions::FolderExists("commonappdata")) Functions::RemoveFolder("commonappdata");
	}
}

bool Extractor::Settlers3::Extract::FullRAWExtract(){
	if(this->gameVersion == VersionNONE) return false;
	Functions::CreateDir("Extracted/");
	Functions::CreateDir("Extracted/S3/");
	Functions::CreateDir("Extracted/S3/GFX/");
	if(this->gameVersion != VersionS3MCD1) Functions::CreateDir("Extracted/S3/SND/");
	Functions::CreateDir("Extracted/S3/MAP/");

	if(this->gameVersion == VersionS3CD2){//Original CD 2
		this->RAWMAPFolderExtract(this->location + "s3/mis_m/a/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3/mis_m/e/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3/mis_m/r/", MT_ORIGINALMISSIONS);
	}else if(this->gameVersion == (VersionS3GOLD1)){//GOLD CD 1
		this->RAWMAPFolderExtract(this->location + "s3qota/mis_m/g/", MT_QOTAMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3qota/mis_m/z/", MT_QOTAMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3/map/tutorial/", MT_TUTORIAL);
	}else if(this->gameVersion == VersionS3MCD1){//MISSION CD
		std::string fileNumbers[5] = {"07","08","09","60","99"};
		for(int i = 0; i < 5; i++)
			this->RAWGFXFileExtract(this->location + "s3update/","s3_" + fileNumbers[i] +".dat");
		this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/a/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/e/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/r/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3mcd/map/multi/", MT_MULTI);
		this->RAWMAPFolderExtract(this->location + "s3mcd/map/single/", MT_SINGLE);
	}else if(this->gameVersion == VersionS3QOTA1){//QUEST OF THE AMAZON CD
		std::string fileNumbers[29] = {"01","03","06","07","08","09","11","12","13","14","15","21","25","27","30","31","33","35","36","40","41","42","43","44","45","46","47","48","99"};
		for(int i = 0; i < 29; i++)
			this->RAWGFXFileExtract(this->location + "S3UPDATE/","S3_" + fileNumbers[i] +".DAT");
		this->RAWSNDFileExtract(this->location + "S3UPDATE/","SND3_00.DAT");
		this->RAWMAPFolderExtract(this->location + "S3QOTA/MIS_M/G/", MT_QOTAMISSIONS);
		this->RAWMAPFolderExtract(this->location + "S3QOTA/MIS_M/Z/", MT_QOTAMISSIONS);
		this->RAWMAPFolderExtract(this->location + "S3QOTA/MAP/MULTI/", MT_MULTI);
		this->RAWMAPFolderExtract(this->location + "S3QOTA/MAP/SINGLE/", MT_SINGLE);
	}else if(this->gameVersion == (VersionS3GOLD2)){//GOLD CD 2
		Functions::ExternalProgram* program = new Functions::ExternalProgram(this->location);
		if(Functions::FolderExists("EXE") == false){
			if(program->CABExtract("s3/install/data.cab") == false) return false;
		}else
			LOGSYSTEM->Log("CABExtract: Already Extracted",1);
		delete program;
		this->RAWGFXFolderExtract("EXE/GFX/");
		this->RAWSNDFolderExtract("EXE/SND/");
		this->RAWMAPFolderExtract("EXE/MULTI/", MT_MULTI);
		this->RAWMAPFolderExtract("EXE/SINGLE/", MT_SINGLE);
		this->RAWMAPFolderExtract("EXE/MAP/TUTORIAL/", MT_TUTORIAL);
		this->RAWMAPFolderExtract("EXE/USER/", MT_USER);
		this->RAWMAPFolderExtract(this->location + "s3/mis_m/a/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3/mis_m/e/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3/mis_m/r/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/a/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/e/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/r/", MT_MCDMISSIONS);
	} else if(this->gameVersion == (VersionS3GOG)){//GOG not installed
		Functions::ExternalProgram* program = new Functions::ExternalProgram(this->location);
		if(Functions::FolderExists("app") == false){
			if(program->GOGExtract() == false) return false;
		}else
			LOGSYSTEM->Log("GOG Extract: Already Extracted",1);
		delete program;
		this->RAWGFXFolderExtract("app/GFX/");
		this->RAWSNDFolderExtract("app/SND/");
		this->RAWMAPFolderExtract("app/S3/MIS_M/A/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract("app/S3/MIS_M/E/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract("app/S3/MIS_M/R/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract("app/S3MCD/MIS_M/A/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract("app/S3MCD/MUS_M/E/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract("app/S3MCD/MIS_M/R/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract("app/S3QOTA/MIS_M/G/", MT_QOTAMISSIONS);
		this->RAWMAPFolderExtract("app/S3QOTA/MIS_M/Z/", MT_QOTAMISSIONS);
		this->RAWMAPFolderExtract("app/Map/MULTI/", MT_MULTI);
		this->RAWMAPFolderExtract("app/Map/SINGLE/", MT_SINGLE);
		this->RAWMAPFolderExtract("app/Map/TUTORIAL/", MT_TUTORIAL);
		this->RAWMAPFolderExtract("app/Map/User/", MT_USER);
	} else if(this->gameVersion == VersionS3CD1){//Original CD 1
		this->RAWGFXFolderExtract(this->location + "s3/gfx/");
		this->RAWSNDFolderExtract(this->location + "s3/snd/");
		this->RAWMAPFolderExtract(this->location + "s3/map/multi/", MT_MULTI);
		this->RAWMAPFolderExtract(this->location + "s3/map/single/", MT_SINGLE);
		this->RAWMAPFolderExtract(this->location + "s3/map/tutorial/", MT_TUTORIAL);
	} else if(this->gameVersion == (VersionS3GOGINSTALL)){//GOG installed
		this->RAWGFXFolderExtract(this->location + "GFX/");
		this->RAWSNDFolderExtract(this->location + "SND/");
		this->RAWMAPFolderExtract(this->location + "S3/MIS_M/A/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract(this->location + "S3/MIS_M/E/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract(this->location + "S3/MIS_M/R/", MT_ORIGINALMISSIONS);
		this->RAWMAPFolderExtract(this->location + "S3MCD/MAP/MIS_M/A/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract(this->location + "S3MCD/MAP/MIS_M/E/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract(this->location + "S3MCD/MAP/MIS_M/R/", MT_MCDMISSIONS);
		this->RAWMAPFolderExtract(this->location + "S3QOTA/MIS_M/G/", MT_QOTAMISSIONS);
		this->RAWMAPFolderExtract(this->location + "S3QOTA/MIS_M/Z/", MT_QOTAMISSIONS);
		this->RAWMAPFolderExtract(this->location + "Map/MULTI/", MT_MULTI);
		this->RAWMAPFolderExtract(this->location + "Map/SINGLE/", MT_SINGLE);
		this->RAWMAPFolderExtract(this->location + "Map/TUTORIAL/", MT_TUTORIAL);
		this->RAWMAPFolderExtract(this->location + "Map/User/", MT_USER);
	} else if(this->gameVersion == (VersionS3DISCINSTALL)){//Disc installed
		this->RAWGFXFolderExtract(this->location + "Gfx/");
		this->RAWSNDFolderExtract(this->location + "Snd/");
		this->RAWMAPFolderExtract(this->location + "Map/multi/", MT_MULTI);
		this->RAWMAPFolderExtract(this->location + "Map/single/", MT_SINGLE);
		this->RAWMAPFolderExtract(this->location + "Map/tutorial/", MT_TUTORIAL);
		this->RAWMAPFolderExtract(this->location + "Map/User/", MT_USER);
	} else if(this->gameVersion == (VersionS3GOLDINSTALL)){//GOLD installed
		this->RAWGFXFolderExtract(this->location + "GFX/");
		this->RAWSNDFolderExtract(this->location + "SND/");
		this->RAWMAPFolderExtract(this->location + "Map/MULTI/", MT_MULTI);
		this->RAWMAPFolderExtract(this->location + "Map/SINGLE/", MT_SINGLE);
		this->RAWMAPFolderExtract(this->location + "Map/TUTORIAL/", MT_TUTORIAL);
		this->RAWMAPFolderExtract(this->location + "Map/User/", MT_USER);
	} else{
		LOGSYSTEM->Error("Detection of Settlers 3 version failed");
		return false;
	}
	return true;
}

bool Extractor::Settlers3::Extract::RAWGFXFileExtract(std::string folder, std::string file){
	if(Functions::FileExists(folder+file)){
		LOGSYSTEM->Log("Open GFX Data File: "+ file,1);
		LOGSYSTEM->Log("Extracting...",1);
		GFXDataType* GFXFile = new GFXDataType(folder+file);
		LOGSYSTEM->Log("Saving...",1);
		Functions::CreateDir("Extracted/");
		Functions::CreateDir("Extracted/S3/");
		Functions::CreateDir("Extracted/S3/GFX/");
		Functions::CreateDir("Extracted/S3/GFX/"+ file);
		GFXFile->SaveToFile("Extracted/S3/GFX/" + file);
		LOGSYSTEM->Log("Closing...",1);
		delete GFXFile;
		return true;
	}else return false;
}

bool Extractor::Settlers3::Extract::RAWSNDFileExtract(std::string folder, std::string file){
	if(Functions::FileExists(folder+file)){
		LOGSYSTEM->Log("Open SND Data File: "+ file,1);
		LOGSYSTEM->Log("Extracting...",1);
		SNDDataType* SNDFile = new SNDDataType(folder+file);
		LOGSYSTEM->Log("Saving...",1);
		Functions::CreateDir("Extracted/");
		Functions::CreateDir("Extracted/S3/");
		Functions::CreateDir("Extracted/S3/SND/");
		Functions::CreateDir("Extracted/S3/SND/"+ file);
		SNDFile->SaveToFile("Extracted/S3/SND/" + file);
		LOGSYSTEM->Log("Closing...",1);
		delete SNDFile;
		return true;
	}else return false;
}

bool Extractor::Settlers3::Extract::RAWMAPFileExtract(std::string folder, std::string file, MapType mapType){
	if(Functions::FileExists(folder+file)){

		LOGSYSTEM->Log("Open MAP File: "+ file,1);
		LOGSYSTEM->Log("Extracting...",1);
		MAPDataType* MAPFile = new MAPDataType(folder+file);
		LOGSYSTEM->Log("Saving...",1);
		Functions::CreateDir("Extracted/");
		Functions::CreateDir("Extracted/S3/");
		Functions::CreateDir("Extracted/S3/MAP/");
		if(mapType != MT_UNKNOWN){
			std::string outFolder = "";
			switch (mapType){
			case MT_ORIGINALMISSIONS:
				outFolder = "Original/";
				break;
			case MT_MCDMISSIONS:
				outFolder = "MCD/";
				break;
			case MT_QOTAMISSIONS:
				outFolder = "QOTA/";
				break;
			case MT_MULTI:
				outFolder = "Multi/";
				break;
			case MT_SINGLE:
				outFolder = "Single/";
				break;
			case MT_TUTORIAL:
				outFolder = "Tutorial/";
				break;
			case MT_USER:
				outFolder = "User/";
				break;
			case MT_UNKNOWN:
				break;
			}
			Functions::CreateDir("Extracted/S3/MAP/" + outFolder);
			Functions::CreateDir("Extracted/S3/MAP/"+ outFolder + file);
			MAPFile->SaveToFile("Extracted/S3/MAP/" + outFolder + file);
			MAPFile->SaveHeaderData("Extracted/S3/MAP/" + outFolder + file);

		}else{
			Functions::CreateDir("Extracted/S3/MAP/" + file);
			MAPFile->SaveToFile("Extracted/S3/MAP/" + file);
			MAPFile->SaveHeaderData("Extracted/S3/MAP/" + file);
		}
		LOGSYSTEM->Log("Closing...",1);
		delete MAPFile;
		return true;
	}else return false;
}

void Extractor::Settlers3::Extract::RAWGFXFolderExtract(std::string folder){
	if(Functions::FolderExists(folder)){
		std::string fileNameFront[4] = {"Siedler3_", "siedler3_", "s3_", "S3_"};
		std::string fileNameBack[5] = {".f8007e01f.dat", ".f8007e01f.dat", ".dat", ".7c003e01f.dat", ".7c003e01f.dat"};
		for(int i = 0; i < 99; i++){
			if (i == 18) i++;
			for(int j = 0; j < 4; j++){
				std::string file = fileNameFront[j];
				file += (i<10?"0":"");
				file += Functions::ToString(i);
				file += fileNameBack[j];
				if(this->RAWGFXFileExtract(folder,file)) break;
			}
		}
	}
}

void Extractor::Settlers3::Extract::RAWSNDFolderExtract(std::string folder){
	if(Functions::FolderExists(folder)){
		std::string fileNames[6] = {"Siedler3_00.dat", "siedler3_00.dat", "Siedler3_01.dat", "siedler3_01.dat", "s3_00.dat", "s3_01.dat"};
		for(int i = 0; i < 6; i++){
			this->RAWSNDFileExtract(folder,fileNames[i]);
		}
	}
}

void Extractor::Settlers3::Extract::RAWMAPFolderExtract(std::string folder, MapType mapType){
	if(Functions::FolderExists(folder)){
		std::vector<std::string>* fileList = Functions::GetFilesInDirectory(folder);
		for(unsigned int i=0; i < fileList->size(); i++){
			this->RAWMAPFileExtract(folder,fileList->at(i),mapType);
		}
	}
}

bool Extractor::Settlers3::Extract::ManualExtract(eType fileType, std::string location){
	size_t pos = location.find_last_of("/");
	if(pos != location.length()-1){
		std::string file = location.substr(pos+1);
		std::string folder = location.substr(0,pos+1);
		switch(fileType){
		case MAP:
			this->RAWMAPFileExtract(folder,file);
			break;
		case GFX:
			this->RAWGFXFileExtract(folder,file);
			break;
		case SND:
			this->RAWSNDFileExtract(folder,file);
			break;
		default:
			return false;
		}

	}else{
		switch(fileType){
		case MAP:
			this->RAWMAPFolderExtract(location);
			break;
		case GFX:
			this->RAWGFXFolderExtract(location);
			break;
		case SND:
			this->RAWSNDFolderExtract(location);
			break;
		default:
			return false;
		}
	}
	return true;
}

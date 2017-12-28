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

Extractor::Settlers3::Extract::Extract(std::string *location,bool GOG,std::string *saveLocation)
	:location(*location),saveLocation(*saveLocation){
	this->gameVersion = CheckGameVersion(*location,GOG);
}

Extractor::Settlers3::Extract::Extract(std::string *saveLocation)
	:saveLocation(*saveLocation){
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
	Functions::CreateDir(this->saveLocation + "/S3/");
	Functions::CreateDir(this->saveLocation + "/S3/GFX/");
	if(this->gameVersion != VersionS3MCD1) Functions::CreateDir(this->saveLocation + "/S3/SND/");
	Functions::CreateDir(this->saveLocation + "/S3/MAP/");

	if(this->gameVersion == VersionS3CD2){//Original CD 2
		std::string s3misma = this->location + "s3/mis_m/a/";
		this->RAWMAPFolderExtract(&s3misma, MT_ORIGINALMISSIONS);
		std::string s3misme = this->location + "s3/mis_m/e/";
		this->RAWMAPFolderExtract(&s3misme, MT_ORIGINALMISSIONS);
		std::string s3miser = this->location + "s3/mis_m/r/";
		this->RAWMAPFolderExtract(&s3miser, MT_ORIGINALMISSIONS);
	}else if(this->gameVersion == (VersionS3GOLD1)){//GOLD CD 1
		std::string s3qtoamismg = this->location + "s3qota/mis_m/g/";
		this->RAWMAPFolderExtract(&s3qtoamismg, MT_QOTAMISSIONS);
		std::string s3qotamismz = this->location + "s3qota/mis_m/z/";
		this->RAWMAPFolderExtract(&s3qotamismz, MT_QOTAMISSIONS);
		std::string s3maptutorial = this->location + "s3/map/tutorial/";
		this->RAWMAPFolderExtract(&s3maptutorial, MT_TUTORIAL);
	}else if(this->gameVersion == VersionS3MCD1){//MISSION CD
		std::string fileNumbers[5] = {"07","08","09","60","99"};
		std::string s3update = this->location + "s3update/";
		for(int i = 0; i < 5; i++){
			std::string s3xxdat = "s3_" + fileNumbers[i] +".dat";
			this->RAWGFXFileExtract(&s3update,&s3xxdat);
		}
		std::string s3mcdmapmisma = this->location + "s3mcd/map/mis_m/a/";
		this->RAWMAPFolderExtract(&s3mcdmapmisma, MT_MCDMISSIONS);
		std::string s3mcdmapmisme = this->location + "s3mcd/map/mis_m/e/";
		this->RAWMAPFolderExtract(&s3mcdmapmisme, MT_MCDMISSIONS);
		std::string s3mcdmapmismr = this->location + "s3mcd/map/mis_m/r/";
		this->RAWMAPFolderExtract(&s3mcdmapmismr, MT_MCDMISSIONS);
		std::string s3mcdmapmulti = this->location + "s3mcd/map/multi/";
		this->RAWMAPFolderExtract(&s3mcdmapmulti, MT_MULTI);
		std::string s3mcdmapsingle = this->location + "s3mcd/map/single/";
		this->RAWMAPFolderExtract(&s3mcdmapsingle, MT_SINGLE);
	}else if(this->gameVersion == VersionS3QOTA1){//QUEST OF THE AMAZON CD
		std::string fileNumbers[29] = {"01","03","06","07","08","09","11","12","13","14","15","21","25","27","30","31","33","35","36","40","41","42","43","44","45","46","47","48","99"};
		std::string s3update = this->location + "S3UPDATE/";
		for(int i = 0; i < 29; i++){
			std::string s3xxdat = "S3_" + fileNumbers[i] +".DAT";
			this->RAWGFXFileExtract(&s3update,&s3xxdat);
		}
		std::string snd300dat  = "SND3_00.DAT";
		this->RAWSNDFileExtract(&s3update,&snd300dat);
		std::string s3qotamismg = this->location + "S3QOTA/MIS_M/G/";
		this->RAWMAPFolderExtract(&s3qotamismg, MT_QOTAMISSIONS);
		std::string s3qotamismz = this->location + "S3QOTA/MIS_M/Z/";
		this->RAWMAPFolderExtract(&s3qotamismz, MT_QOTAMISSIONS);
		std::string s3qotamapmulti = this->location + "S3QOTA/MAP/MULTI/";
		this->RAWMAPFolderExtract(&s3qotamapmulti, MT_MULTI);
		std::string s3qotamapsingle = this->location + "S3QOTA/MAP/SINGLE/";
		this->RAWMAPFolderExtract(&s3qotamapsingle, MT_SINGLE);
	}else if(this->gameVersion == (VersionS3GOLD2)){//GOLD CD 2
		Functions::ExternalProgram* program = new Functions::ExternalProgram(&this->location);
		if(Functions::FolderExists("EXE") == false){
			if(program->CABExtract("s3/install/data.cab") == false) {
				delete program;
				return false;
			}
		}else
			LOGSYSTEM->Log("CABExtract: Already Extracted",1);
		delete program;
		std::string exegfx = "EXE/GFX/";
		this->RAWGFXFolderExtract(&exegfx);
		std::string exesnd = "EXE/SND/";
		this->RAWSNDFolderExtract(&exesnd);
		std::string exemulti= "EXE/MULTI/";
		this->RAWMAPFolderExtract(&exemulti, MT_MULTI);
		std::string exesingle = "EXE/SINGLE/";
		this->RAWMAPFolderExtract(&exesingle, MT_SINGLE);
		std::string exemaptutorial = "EXE/MAP/TUTORIAL/";
		this->RAWMAPFolderExtract(&exemaptutorial, MT_TUTORIAL);
		std::string exeuser = "EXE/USER/";
		this->RAWMAPFolderExtract(&exeuser, MT_USER);
		std::string s3misma = this->location + "s3/mis_m/a/";
		this->RAWMAPFolderExtract(&s3misma, MT_ORIGINALMISSIONS);
		std::string s3misme = this->location + "s3/mis_m/e/";
		this->RAWMAPFolderExtract(&s3misme, MT_ORIGINALMISSIONS);
		std::string s3mismr = this->location + "s3/mis_m/r/";
		this->RAWMAPFolderExtract(&s3mismr, MT_ORIGINALMISSIONS);
		std::string s3mcdmapmisma = this->location + "s3mcd/map/mis_m/a/";
		this->RAWMAPFolderExtract(&s3mcdmapmisma, MT_MCDMISSIONS);
		std::string s3mcdmapmisme = this->location + "s3mcd/map/mis_m/e/";
		this->RAWMAPFolderExtract(&s3mcdmapmisme, MT_MCDMISSIONS);
		std::string s3mcdmapmismr = this->location + "s3mcd/map/mis_m/r/";
		this->RAWMAPFolderExtract(&s3mcdmapmismr, MT_MCDMISSIONS);
	} else if(this->gameVersion == (VersionS3GOG)){//GOG not installed
		Functions::ExternalProgram* program = new Functions::ExternalProgram(&this->location);
		if(Functions::FolderExists("app") == false){
			if(program->GOGExtract() == false) {
				delete program;
				return false;
			}
		}else
			LOGSYSTEM->Log("GOG Extract: Already Extracted",1);
		delete program;
		std::string appgfx= "app/GFX/";
		this->RAWGFXFolderExtract(&appgfx);
		std::string appsnd = "app/SND/";
		this->RAWSNDFolderExtract(&appsnd);
		std::string apps3misma = "app/S3/MIS_M/A/";
		this->RAWMAPFolderExtract(&apps3misma, MT_ORIGINALMISSIONS);
		std::string apps3misme = "app/S3/MIS_M/E/";
		this->RAWMAPFolderExtract(&apps3misme, MT_ORIGINALMISSIONS);
		std::string apps3mismr= "app/S3/MIS_M/R/";
		this->RAWMAPFolderExtract(&apps3mismr, MT_ORIGINALMISSIONS);
		std::string apps3mcdmisma = "app/S3MCD/MIS_M/A/";
		this->RAWMAPFolderExtract(&apps3mcdmisma, MT_MCDMISSIONS);
		std::string apps3mcdmisme = "app/S3MCD/MIS_M/E/";
		this->RAWMAPFolderExtract(&apps3mcdmisme, MT_MCDMISSIONS);
		std::string apps3mcdmismr = "app/S3MCD/MIS_M/R/";
		this->RAWMAPFolderExtract(&apps3mcdmismr, MT_MCDMISSIONS);
		std::string apps3qotamismg = "app/S3QOTA/MIS_M/G/";
		this->RAWMAPFolderExtract(&apps3qotamismg, MT_QOTAMISSIONS);
		std::string apps3qotamismz = "app/S3QOTA/MIS_M/Z/";
		this->RAWMAPFolderExtract(&apps3qotamismz, MT_QOTAMISSIONS);
		std::string appmapmulti = "app/Map/MULTI/";
		this->RAWMAPFolderExtract(&appmapmulti, MT_MULTI);
		std::string appmapsingle = "app/Map/SINGLE/";
		this->RAWMAPFolderExtract(&appmapsingle, MT_SINGLE);
		std::string appmaptutorial = "app/Map/TUTORIAL/";
		this->RAWMAPFolderExtract(&appmaptutorial, MT_TUTORIAL);
		std::string appmapuser = "app/Map/User/";
		this->RAWMAPFolderExtract(&appmapuser, MT_USER);
	} else if(this->gameVersion == VersionS3CD1){//Original CD 1
		std::string s3gfx = this->location + "s3/gfx/";
		this->RAWGFXFolderExtract(&s3gfx);
		std::string s3snd = this->location + "s3/snd/";
		this->RAWSNDFolderExtract(&s3snd);
		std::string s3mapmulti = this->location + "s3/map/multi/";
		this->RAWMAPFolderExtract(&s3mapmulti, MT_MULTI);
		std::string s3mapsingle = this->location + "s3/map/single/";
		this->RAWMAPFolderExtract(&s3mapsingle, MT_SINGLE);
		std::string s3maptutorial = this->location + "s3/map/tutorial/";
		this->RAWMAPFolderExtract(&s3maptutorial, MT_TUTORIAL);
	} else if(this->gameVersion == (VersionS3GOGINSTALL)){//GOG installed
		std::string gfx = this->location + "GFX/";
		this->RAWGFXFolderExtract(&gfx);
		std::string snd = this->location + "SND/";
		this->RAWSNDFolderExtract(&snd);
		std::string s3misma = this->location + "S3/MIS_M/A/";
		this->RAWMAPFolderExtract(&s3misma, MT_ORIGINALMISSIONS);
		std::string s3misme = this->location + "S3/MIS_M/E/";
		this->RAWMAPFolderExtract(&s3misme, MT_ORIGINALMISSIONS);
		std::string s3mismr = this->location + "S3/MIS_M/R/";
		this->RAWMAPFolderExtract(&s3misme, MT_ORIGINALMISSIONS);
		std::string s3mcdmapmisma = this->location + "S3MCD/MAP/MIS_M/A/";
		this->RAWMAPFolderExtract(&s3mcdmapmisma, MT_MCDMISSIONS);
		std::string s3mcdmapmisme = this->location + "S3MCD/MAP/MIS_M/E/";
		this->RAWMAPFolderExtract(&s3mcdmapmisme, MT_MCDMISSIONS);
		std::string s3mcdmapmismr = this->location + "S3MCD/MAP/MIS_M/R/";
		this->RAWMAPFolderExtract(&s3mcdmapmismr, MT_MCDMISSIONS);
		std::string s3qotamismg = this->location + "S3QOTA/MIS_M/G/";
		this->RAWMAPFolderExtract(&s3qotamismg, MT_QOTAMISSIONS);
		std::string s3qotamismz = this->location + "S3QOTA/MIS_M/Z/";
		this->RAWMAPFolderExtract(&s3qotamismz , MT_QOTAMISSIONS);
		std::string mapmulti = this->location + "Map/MULTI/";
		this->RAWMAPFolderExtract(&mapmulti, MT_MULTI);
		std::string mapsingle = this->location + "Map/SINGLE/";
		this->RAWMAPFolderExtract(&mapsingle, MT_SINGLE);
		std::string maptutorial = this->location + "Map/TUTORIAL/";
		this->RAWMAPFolderExtract(&maptutorial, MT_TUTORIAL);
		std::string mapuser = this->location + "Map/User/";
		this->RAWMAPFolderExtract(&mapuser, MT_USER);
	} else if(this->gameVersion == (VersionS3DISCINSTALL)){//Disc installed
		std::string gfx = this->location + "Gfx/";
		this->RAWGFXFolderExtract(&gfx);
		std::string snd = this->location + "Snd/";
		this->RAWSNDFolderExtract(&snd);
		std::string mapmulti = this->location + "Map/multi/";
		this->RAWMAPFolderExtract(&mapmulti, MT_MULTI);
		std::string mapsingle = this->location + "Map/single/";
		this->RAWMAPFolderExtract(&mapsingle, MT_SINGLE);
		std::string maptutorial = this->location + "Map/tutorial/";
		this->RAWMAPFolderExtract(&maptutorial, MT_TUTORIAL);
		std::string mapuser = this->location + "Map/User/";
		this->RAWMAPFolderExtract(&mapuser, MT_USER);
	} else if(this->gameVersion == (VersionS3GOLDINSTALL)){//GOLD installed
		std::string gfx = this->location + "GFX/";
		this->RAWGFXFolderExtract(&gfx);
		std::string snd = this->location + "SND/";
		this->RAWSNDFolderExtract(&snd);
		std::string mapmulti = this->location + "Map/MULTI/";
		this->RAWMAPFolderExtract(&mapmulti, MT_MULTI);
		std::string mapsingle = this->location + "Map/SINGLE/";
		this->RAWMAPFolderExtract(&mapsingle, MT_SINGLE);
		std::string maptutorial = this->location + "Map/TUTORIAL/";
		this->RAWMAPFolderExtract(&maptutorial, MT_TUTORIAL);
		std::string mapuser = this->location + "Map/User/";
		this->RAWMAPFolderExtract(&mapuser, MT_USER);
	} else{
		LOGSYSTEM->Error("Detection of Settlers 3 version failed");
		return false;
	}
	return true;
}

bool Extractor::Settlers3::Extract::RAWGFXFileExtract(std::string *folder, std::string *file){
	if(Functions::FileExists(*folder+*file)){
		LOGSYSTEM->Log("Open GFX Data File: "+ *file,1);
		LOGSYSTEM->Log("Extracting...",1);
		GFXDataType* GFXFile = new GFXDataType(*folder+*file);
		LOGSYSTEM->Log("Saving...",1);

		Functions::CreateDir(this->saveLocation + "/S3/");
		Functions::CreateDir(this->saveLocation + "/S3/GFX/");
		Functions::CreateDir(this->saveLocation + "/S3/GFX/"+ *file);
		GFXFile->SaveToFile(this->saveLocation + "/S3/GFX/" + *file);
		LOGSYSTEM->Log("Closing...",1);
		delete GFXFile;
		return true;
	}else return false;
}

bool Extractor::Settlers3::Extract::RAWSNDFileExtract(std::string *folder, std::string *file){
	if(Functions::FileExists(*folder+*file)){
		LOGSYSTEM->Log("Open SND Data File: "+ *file,1);
		LOGSYSTEM->Log("Extracting...",1);
		SNDDataType* SNDFile = new SNDDataType(*folder+*file);
		LOGSYSTEM->Log("Saving...",1);
		Functions::CreateDir(this->saveLocation + "/");
		Functions::CreateDir(this->saveLocation + "/S3/");
		Functions::CreateDir(this->saveLocation + "/S3/SND/");
		Functions::CreateDir(this->saveLocation + "/S3/SND/"+ *file);
		SNDFile->SaveToFile(this->saveLocation + "/S3/SND/" + *file);
		LOGSYSTEM->Log("Closing...",1);
		delete SNDFile;
		return true;
	}else return false;
}

bool Extractor::Settlers3::Extract::RAWMAPFileExtract(std::string *folder, std::string *file, MapType mapType){
	if(Functions::FileExists(*folder+*file)){

		LOGSYSTEM->Log("Open MAP File: "+ *file,1);
		LOGSYSTEM->Log("Extracting...",1);
		MAPDataType* MAPFile = new MAPDataType(*folder+*file);
		LOGSYSTEM->Log("Saving...",1);
		Functions::CreateDir(this->saveLocation + "/");
		Functions::CreateDir(this->saveLocation + "/S3/");
		Functions::CreateDir(this->saveLocation + "/S3/MAP/");
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
			Functions::CreateDir(this->saveLocation + "/S3/MAP/" + outFolder);
			Functions::CreateDir(this->saveLocation + "/S3/MAP/"+ outFolder + *file);
			MAPFile->SaveToFile(this->saveLocation + "/S3/MAP/" + outFolder + *file);
			MAPFile->SaveHeaderData(this->saveLocation + "/S3/MAP/" + outFolder + *file);

		}else{
			Functions::CreateDir(this->saveLocation + "/S3/MAP/" + *file);
			MAPFile->SaveToFile(this->saveLocation + "/S3/MAP/" + *file);
			MAPFile->SaveHeaderData(this->saveLocation + "/S3/MAP/" + *file);
		}
		LOGSYSTEM->Log("Closing...",1);
		delete MAPFile;
		return true;
	}else return false;
}

void Extractor::Settlers3::Extract::RAWGFXFolderExtract(std::string *folder){
	if(Functions::FolderExists(*folder)){
		std::string fileNameFront[4] = {"Siedler3_", "siedler3_", "s3_", "S3_"};
		std::string fileNameBack[5] = {".f8007e01f.dat", ".f8007e01f.dat", ".dat", ".7c003e01f.dat", ".7c003e01f.dat"};
		for(int i = 0; i < 99; i++){
			if (i == 18) i++;
			for(int j = 0; j < 4; j++){
				std::string file = fileNameFront[j];
				file += (i<10?"0":"");
				file += Functions::ToString(i);
				file += fileNameBack[j];
				if(this->RAWGFXFileExtract(folder,&file)) break;
			}
		}
	}
}

void Extractor::Settlers3::Extract::RAWSNDFolderExtract(std::string *folder){
	if(Functions::FolderExists(*folder)){
		std::string fileNames[6] = {"Siedler3_00.dat", "siedler3_00.dat", "Siedler3_01.dat", "siedler3_01.dat", "s3_00.dat", "s3_01.dat"};
		for(int i = 0; i < 6; i++){
			this->RAWSNDFileExtract(folder,&fileNames[i]);
		}
	}
}

void Extractor::Settlers3::Extract::RAWMAPFolderExtract(std::string *folder, MapType mapType){
	if(Functions::FolderExists(*folder)){
		std::vector<std::string>* fileList = Functions::GetFilesInDirectory(*folder);
		for(unsigned int i=0; i < fileList->size(); i++){
			this->RAWMAPFileExtract(folder,&fileList->at(i),mapType);
		}
	}
}

bool Extractor::Settlers3::Extract::ManualExtract(eType fileType, std::string *location){
	size_t pos = location->find_last_of("/");
	if(pos != location->length()-1){
		std::string file = location->substr(pos+1);
		std::string folder = location->substr(0,pos+1);
		switch(fileType){
		case MAP:
			this->RAWMAPFileExtract(&folder,&file);
			break;
		case GFX:
			this->RAWGFXFileExtract(&folder,&file);
			break;
		case SND:
			this->RAWSNDFileExtract(&folder,&file);
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

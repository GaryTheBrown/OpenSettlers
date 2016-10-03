//============================================================================
// Name        : SortedExtractor.cpp
// Author      : Gary_The_Brown
// Copyright   :
// Description :
//============================================================================

#include "SortedExtractor.h"

Extractor::Settlers3::SortedExtractor::SortedExtractor(std::string locationOfFiles, unsigned char gameVersion)
	:gameVersion(gameVersion),
	 locationofFiles(locationOfFiles){
}
bool Extractor::Settlers3::SortedExtractor::Extract(bool extendible){
	if(this->gameVersion == VersionNONE) return false;

	Functions::CreateDir("Games/");
	Functions::CreateDir(this->extractionLocation);


//Make these else if's store locations and file names (counter in the middle of pair)
	if(this->gameVersion == VersionS3CD1){//Original CD 1
		this->locationofGFXFiles = "s3/gfx/";
		this->GFXFileName = std::make_pair("s3_",".dat");
		this->locationofSNDFiles = "s3/snd/";
		this->SNDFileName = std::make_pair("s3_",".dat");
		//this->RAWMAPFolderExtract(this->location + "s3/map/multi/", MT_MULTI);
		//this->RAWMAPFolderExtract(this->location + "s3/map/single/", MT_SINGLE);
		//this->RAWMAPFolderExtract(this->location + "s3/map/tutorial/", MT_TUTORIAL);
	} else if(this->gameVersion == VersionS3CD2){//Original CD 2
		//this->RAWMAPFolderExtract(this->location + "s3/mis_m/a/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3/mis_m/e/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3/mis_m/r/", MT_ORIGINALMISSIONS);
	}else if(this->gameVersion == VersionS3MCD1){//MISSION CD
		this->locationofGFXFiles = "s3update/";
		this->GFXFileName = std::make_pair("s3_",".dat");

		//this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/a/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/e/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/r/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3mcd/map/multi/", MT_MULTI);
		//this->RAWMAPFolderExtract(this->location + "s3mcd/map/single/", MT_SINGLE);

	}else if(this->gameVersion == VersionS3QOTA1){//QUEST OF THE AMAZON CD
		this->locationofGFXFiles = "S3UPDATE/";
		this->GFXFileName = std::make_pair("S3_",".DAT");
		this->locationofSNDFiles = "S3UPDATE/";
		this->SNDFileName = std::make_pair("SND3_",".DAT");

		//this->RAWMAPFolderExtract(this->location + "S3QOTA/MIS_M/G/", MT_QOTAMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "S3QOTA/MIS_M/Z/", MT_QOTAMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "S3QOTA/MAP/MULTI/", MT_MULTI);
		//this->RAWMAPFolderExtract(this->location + "S3QOTA/MAP/SINGLE/", MT_SINGLE);
	}else if(this->gameVersion == (VersionS3GOLD1)){//GOLD CD 1

		//this->RAWMAPFolderExtract(this->location + "s3qota/mis_m/g/", MT_QOTAMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3qota/mis_m/z/", MT_QOTAMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3/map/tutorial/", MT_TUTORIAL);
	}else if(this->gameVersion == (VersionS3GOLD2)){//GOLD CD 2
		//Extract from Cab
		Functions::ExternalProgram* program = new Functions::ExternalProgram(this->locationofFiles);
		if(Functions::FolderExists("EXE") == false){
			if(program->CABExtract("s3/install/data.cab") == false) return false;
		}else
			LOGSYSTEM->Log("CABExtract: Already Extracted",1);
		delete program;

		this->locationofGFXFiles = "EXE/GFX/";
		this->GFXFileName = std::make_pair("Siedler3_",".f8007e01f.dat");
		this->locationofSNDFiles = "EXE/SND/";
		this->SNDFileName = std::make_pair("Siedler3_",".dat");

		//this->RAWMAPFolderExtract("EXE/MULTI/", MT_MULTI);
		//this->RAWMAPFolderExtract("EXE/SINGLE/", MT_SINGLE);
		//this->RAWMAPFolderExtract("EXE/MAP/TUTORIAL/", MT_TUTORIAL);
		//this->RAWMAPFolderExtract("EXE/USER/", MT_USER);
		//this->RAWMAPFolderExtract(this->location + "s3/mis_m/a/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3/mis_m/e/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3/mis_m/r/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/a/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/e/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/r/", MT_MCDMISSIONS);
	} else if(this->gameVersion == (VersionS3GOG)){//GOG not installed
		//Extract From EXE
		Functions::ExternalProgram* program = new Functions::ExternalProgram(this->locationofFiles);
		if(Functions::FolderExists("app") == false){
			if(program->GOGExtract() == false) return false;
		}else
			LOGSYSTEM->Log("GOG Extract: Already Extracted",1);
		delete program;

		this->locationofGFXFiles = "app/GFX/";
		this->GFXFileName = std::make_pair("Siedler3_",".f8007e01f.dat");
		this->locationofSNDFiles = "app/SND/";
		this->SNDFileName = std::make_pair("Siedler3_",".dat");

		//this->RAWMAPFolderExtract("app/S3/MIS_M/A/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract("app/S3/MIS_M/E/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract("app/S3/MIS_M/R/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract("app/S3MCD/MIS_M/A/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract("app/S3MCD/MUS_M/E/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract("app/S3MCD/MIS_M/R/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract("app/S3QOTA/MIS_M/G/", MT_QOTAMISSIONS);
		//this->RAWMAPFolderExtract("app/S3QOTA/MIS_M/Z/", MT_QOTAMISSIONS);
		//this->RAWMAPFolderExtract("app/Map/MULTI/", MT_MULTI);
		//this->RAWMAPFolderExtract("app/Map/SINGLE/", MT_SINGLE);
		//this->RAWMAPFolderExtract("app/Map/TUTORIAL/", MT_TUTORIAL);
		//this->RAWMAPFolderExtract("app/Map/User/", MT_USER);
	} else if(this->gameVersion == (VersionS3GOGINSTALL)){//GOG installed
		this->locationofGFXFiles = "GFX/";
		this->GFXFileName = std::make_pair("Siedler3_",".f8007e01f.dat");
		this->locationofSNDFiles = "SND/";
		this->SNDFileName = std::make_pair("Siedler3_",".dat");

		//this->RAWMAPFolderExtract(this->location + "S3/MIS_M/A/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "S3/MIS_M/E/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "S3/MIS_M/R/", MT_ORIGINALMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "S3MCD/MAP/MIS_M/A/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "S3MCD/MAP/MIS_M/E/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "S3MCD/MAP/MIS_M/R/", MT_MCDMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "S3QOTA/MIS_M/G/", MT_QOTAMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "S3QOTA/MIS_M/Z/", MT_QOTAMISSIONS);
		//this->RAWMAPFolderExtract(this->location + "Map/MULTI/", MT_MULTI);
		//this->RAWMAPFolderExtract(this->location + "Map/SINGLE/", MT_SINGLE);
		//this->RAWMAPFolderExtract(this->location + "Map/TUTORIAL/", MT_TUTORIAL);
		//this->RAWMAPFolderExtract(this->location + "Map/User/", MT_USER);
	} else if(this->gameVersion == (VersionS3DISCINSTALL)){//Disc installed
		this->locationofGFXFiles = "Gfx/";
		this->GFXFileName = std::make_pair("siedler3_",".f8007e01f.dat");
		this->locationofSNDFiles = "Snd/";
		this->SNDFileName = std::make_pair("siedler3_",".dat");

		//this->RAWMAPFolderExtract(this->location + "Map/multi/", MT_MULTI);
		//this->RAWMAPFolderExtract(this->location + "Map/single/", MT_SINGLE);
		//this->RAWMAPFolderExtract(this->location + "Map/tutorial/", MT_TUTORIAL);
		//this->RAWMAPFolderExtract(this->location + "Map/User/", MT_USER);
	} else if(this->gameVersion == (VersionS3GOLDINSTALL)){//GOLD installed
		this->locationofGFXFiles = "GFX/";
		this->GFXFileName = std::make_pair("Siedler3_",".f8007e01f.dat");
		this->locationofSNDFiles = "SND/";
		this->SNDFileName = std::make_pair("Siedler3_",".dat");

		//this->RAWMAPFolderExtract(this->location + "Map/MULTI/", MT_MULTI);
		//this->RAWMAPFolderExtract(this->location + "Map/SINGLE/", MT_SINGLE);
		//this->RAWMAPFolderExtract(this->location + "Map/TUTORIAL/", MT_TUTORIAL);
		//this->RAWMAPFolderExtract(this->location + "Map/User/", MT_USER);
	} else{
		LOGSYSTEM->Error("Detection of Settlers 3 version failed");
	}


	this->Landscape();
	this->GUI(extendible);
	return true;
}


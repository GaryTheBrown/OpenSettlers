/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Convert.h"

void Converter::Settlers3::Convert::SetupData(){
	switch(this->data.version){
		case Extractor::Settlers3::VersionNONE:
		default:{
			LOGSYSTEM->Error("Detection of Settlers 3 version failed");
			this->somethingToExtract = false;
			break;
		}
		case Extractor::Settlers3::VersionS3CD1:{
			this->data.locationofGFXFiles = this->data.locationofFiles + "s3/gfx/";
			this->data.GFXFileName = std::make_pair("s3_",".dat");
			this->data.locationofSNDFiles = this->data.locationofFiles + "s3/snd/";
			this->data.SNDFileName = std::make_pair("s3_",".dat");
			//this->RAWMAPFolderExtract(this->location + "s3/map/multi/", MT_MULTI);
			//this->RAWMAPFolderExtract(this->location + "s3/map/single/", MT_SINGLE);
			//this->RAWMAPFolderExtract(this->location + "s3/map/tutorial/", MT_TUTORIAL);
			break;
		}
		case Extractor::Settlers3::VersionS3CD2:{
			//this->RAWMAPFolderExtract(this->location + "s3/mis_m/a/", MT_ORIGINALMISSIONS);
			//this->RAWMAPFolderExtract(this->location + "s3/mis_m/e/", MT_ORIGINALMISSIONS);
			//this->RAWMAPFolderExtract(this->location + "s3/mis_m/r/", MT_ORIGINALMISSIONS);
			this->somethingToExtract = false;
			break;
		}
		case Extractor::Settlers3::VersionS3MCD1:{
			this->data.locationofGFXFiles = this->data.locationofFiles + "s3update/";
			this->data.GFXFileName = std::make_pair("s3_",".dat");

			//this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/a/", MT_MCDMISSIONS);
			//this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/e/", MT_MCDMISSIONS);
			//this->RAWMAPFolderExtract(this->location + "s3mcd/map/mis_m/r/", MT_MCDMISSIONS);
			//this->RAWMAPFolderExtract(this->location + "s3mcd/map/multi/", MT_MULTI);
			//this->RAWMAPFolderExtract(this->location + "s3mcd/map/single/", MT_SINGLE);
			break;
		}
		case Extractor::Settlers3::VersionS3QOTA1:{
			this->data.locationofGFXFiles = this->data.locationofFiles + "S3UPDATE/";
			this->data.GFXFileName = std::make_pair("S3_",".DAT");
			this->data.locationofSNDFiles = this->data.locationofFiles + "S3UPDATE/";
			this->data.SNDFileName = std::make_pair("SND3_",".DAT");

			//this->RAWMAPFolderExtract(this->location + "S3QOTA/MIS_M/G/", MT_QOTAMISSIONS);
			//this->RAWMAPFolderExtract(this->location + "S3QOTA/MIS_M/Z/", MT_QOTAMISSIONS);
			//this->RAWMAPFolderExtract(this->location + "S3QOTA/MAP/MULTI/", MT_MULTI);
			//this->RAWMAPFolderExtract(this->location + "S3QOTA/MAP/SINGLE/", MT_SINGLE);
			break;
		}
		case Extractor::Settlers3::VersionS3GOLD1:{
			//this->RAWMAPFolderExtract(this->location + "s3qota/mis_m/g/", MT_QOTAMISSIONS);
			//this->RAWMAPFolderExtract(this->location + "s3qota/mis_m/z/", MT_QOTAMISSIONS);
			//this->RAWMAPFolderExtract(this->location + "s3/map/tutorial/", MT_TUTORIAL);
			this->somethingToExtract = false;
			break;
		}
		case Extractor::Settlers3::VersionS3GOLD2:{
			//Extract from Cab
			Functions::ExternalProgram* program = new Functions::ExternalProgram(this->data.locationofFiles);
			if(Functions::FolderExists("EXE") == false){
				if(program->CABExtract("s3/install/data.cab") == false){
					this->somethingToExtract = false;
					return;
				}
			}else
				LOGSYSTEM->Log("CABExtract: Already Extracted",1);
			delete program;

			this->data.locationofGFXFiles = "EXE/GFX/";
			this->data.GFXFileName = std::make_pair("Siedler3_",".f8007e01f.dat");
			this->data.locationofSNDFiles = "EXE/SND/";
			this->data.SNDFileName = std::make_pair("Siedler3_",".dat");

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
			break;
		}
		case Extractor::Settlers3::VersionS3GOG:{
			//Extract From EXE
			Functions::ExternalProgram* program = new Functions::ExternalProgram(this->data.locationofFiles);
			if(Functions::FolderExists("app") == false){
				if(program->GOGExtract() == false){
					this->somethingToExtract = false;
					return;
				}
			}else
				LOGSYSTEM->Log("GOG Extract: Already Extracted",1);
			delete program;

			this->data.locationofGFXFiles = "app/GFX/";
			this->data.GFXFileName = std::make_pair("Siedler3_",".f8007e01f.dat");
			this->data.locationofSNDFiles = "app/SND/";
			this->data.SNDFileName = std::make_pair("Siedler3_",".dat");

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
			break;
		}
		case Extractor::Settlers3::VersionS3GOGINSTALL:{
			this->data.locationofGFXFiles = this->data.locationofFiles + "GFX/";
			this->data.GFXFileName = std::make_pair("Siedler3_",".f8007e01f.dat");
			this->data.locationofSNDFiles = this->data.locationofFiles + "SND/";
			this->data.SNDFileName = std::make_pair("Siedler3_",".dat");

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
			break;
		}
		case Extractor::Settlers3::VersionS3DISCINSTALL:{
			this->data.locationofGFXFiles = this->data.locationofFiles + "Gfx/";
			this->data.GFXFileName = std::make_pair("siedler3_",".f8007e01f.dat");
			this->data.locationofSNDFiles = this->data.locationofFiles + "Snd/";
			this->data.SNDFileName = std::make_pair("siedler3_",".dat");

			//this->RAWMAPFolderExtract(this->location + "Map/multi/", MT_MULTI);
			//this->RAWMAPFolderExtract(this->location + "Map/single/", MT_SINGLE);
			//this->RAWMAPFolderExtract(this->location + "Map/tutorial/", MT_TUTORIAL);
			//this->RAWMAPFolderExtract(this->location + "Map/User/", MT_USER);
			break;
		}
		case Extractor::Settlers3::VersionS3GOLDINSTALL:{
			this->data.locationofGFXFiles = this->data.locationofFiles + "GFX/";
			this->data.GFXFileName = std::make_pair("Siedler3_",".f8007e01f.dat");
			this->data.locationofSNDFiles = this->data.locationofFiles + "SND/";
			this->data.SNDFileName = std::make_pair("Siedler3_",".dat");

			//this->RAWMAPFolderExtract(this->location + "Map/MULTI/", MT_MULTI);
			//this->RAWMAPFolderExtract(this->location + "Map/SINGLE/", MT_SINGLE);
			//this->RAWMAPFolderExtract(this->location + "Map/TUTORIAL/", MT_TUTORIAL);
			//this->RAWMAPFolderExtract(this->location + "Map/User/", MT_USER);
			break;
		}
	}
}


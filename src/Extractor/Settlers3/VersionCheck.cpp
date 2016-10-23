/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "VersionCheck.h"

Extractor::Settlers3::VersionS3 Extractor::Settlers3::CheckGameVersion(std::string location, bool GOG){
	//GOG INSTALLERS.
	if(GOG){
		LOGSYSTEM->Message("Detected Settlers 3 GOG Installer");
		return VersionS3GOG;
	}
	//DISC INSTALLED
	else if(Functions::FileExists(location + "s3.exe")){
		if(Functions::FolderExists(location + "EXTRAS")){
			LOGSYSTEM->Message("Detected Settlers 3 GOLD Installed Version");
			return VersionS3GOLDINSTALL;
		}else{
			LOGSYSTEM->Message("Detected Settlers 3 Installed Version");
			return VersionS3DISCINSTALL;
		}
	}
	//GOG INSTALLED
	else if(Functions::FileExists(location + "S3.EXE")){
		LOGSYSTEM->Message("Detected Settlers 3 GOG Installed Version");
		return VersionS3GOGINSTALL;
	}
	//DISCS
	else if((Functions::FileExists(location + "S3GOLD1.DAT"))||(Functions::FileExists(location + "s3gold1.dat"))){
		LOGSYSTEM->Message("Detected Settlers 3 GOLD CD 1");
		return VersionS3GOLD1;
	}else if((Functions::FileExists(location + "S3GOLD2.DAT"))||(Functions::FileExists(location + "s3gold2.dat"))){
		LOGSYSTEM->Message("Detected Settlers 3 GOLD CD 2");
		return VersionS3GOLD2;
	}else if((Functions::FileExists(location + "S3CD1.DAT"  ))||(Functions::FileExists(location + "s3cd1.dat"  ))){
		LOGSYSTEM->Message("Detected Settlers 3 CD 1");
		return VersionS3CD1;
	}else if((Functions::FileExists(location + "S3CD2.DAT"  ))||(Functions::FileExists(location + "s3cd2.dat"  ))){
		LOGSYSTEM->Message("Detected Settlers 3 CD 2");
		return VersionS3CD2;
	}else if((Functions::FileExists(location + "S3MCD1.DAT" ))||(Functions::FileExists(location + "s3mcd1.dat" ))){
		LOGSYSTEM->Message("Detected Settlers 3 Mission CD");
		return VersionS3MCD1;
	}else if((Functions::FileExists(location + "S3QOTA1.DAT"))||(Functions::FileExists(location + "s3qota1.dat"))){
		LOGSYSTEM->Message("Detected Settlers 3 Quest Of The Amazon CD");
		return VersionS3QOTA1;
	}
	LOGSYSTEM->Error("Detection of Version Failed");
	return VersionNONE;
}

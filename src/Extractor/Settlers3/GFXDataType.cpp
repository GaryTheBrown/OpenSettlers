/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "../Settlers3/GFXDataType.h"

Extractor::Settlers3::GFXDataType::GFXDataType(std::string file){

	if (Functions::FileExists(file) == true){
		Functions::DataReader* reader = new Functions::DataReader(file);
		unsigned int headCode = reader->ReadInt();

		//Make sure file is for Settlers 3
		if (headCode != 0x041304){
			LOGSYSTEM->Error(file + "is not a Settlers 3 GFX File.");
		}else{
			LOGSYSTEM->Log("Reading Header.",2);
			this->header = new GFXHeader(reader);
			LOGSYSTEM->Log("Reading Text Data.",2);
			this->text = new GFXText(reader,this->header->OffsetData());
			LOGSYSTEM->Log("Reading Landscapes.",2);
			this->landscape = new GFXLandscape(reader,this->header->OffsetLandscape(),this->header->ColourCode());
			LOGSYSTEM->Log("Reading GUIs.",2);
			this->gui = new GFXGUI(reader,this->header->OffsetGui(),this->header->ColourCode());
			LOGSYSTEM->Log("Reading Objects.",2);
			this->object = new GFXObject(reader,this->header->OffsetObject(),this->header->ColourCode());
			LOGSYSTEM->Log("Reading Torsos.",2);
			this->torso = new GFXTorso(reader,this->header->OffsetTorso(),Palette);
			LOGSYSTEM->Log("Reading Shadows.",2);
			this->shadow = new GFXShadow(reader,this->header->OffsetShadow());
			LOGSYSTEM->Log("Reading Animations.",2);
			this->animation = new GFXAnimation(reader,this->header->OffsetAnimation());
			LOGSYSTEM->Log("Reading Palettes.",2);
			this->palette = new GFXPalette(reader,this->header->OffsetPalette(),this->header->ColourCode());
			LOGSYSTEM->Log("Finished Reading Data To Memory.",2);
		}
		if (reader != NULL)delete reader;
	}
}

Extractor::Settlers3::GFXDataType::~GFXDataType(){
	if(this->header != NULL){
		LOGSYSTEM->Log("Clean up Header...",2);
		delete this->header;
	}
	if(this->text != NULL){
		LOGSYSTEM->Log("Clean up Text Data...",2);
		delete this->text;
	}

	if(this->landscape != NULL){
		LOGSYSTEM->Log("Clean up Landscapes...",2);
		delete this->landscape;
	}
	if(this->gui != NULL){
		LOGSYSTEM->Log("Clean up GUIs...",2);
		delete this->gui;
	}
	if(this->object != NULL){
		LOGSYSTEM->Log("Clean up Objects...",2);
		delete this->object;
	}
	if(this->torso != NULL){
		LOGSYSTEM->Log("Clean up Torsos...",2);
		delete this->torso;
	}
	if(this->shadow != NULL){
		LOGSYSTEM->Log("Clean up Shadows...",2);
		delete this->shadow;
	}
	if(this->animation != NULL){
		LOGSYSTEM->Log("Clean up Animations...",2);
		delete this->animation;
	}
	if(this->palette != NULL){
		LOGSYSTEM->Log("Clean up Palettes...",2);
		delete this->palette;
	}
	LOGSYSTEM->Log("Finished Clean up.",2);
}

void Extractor::Settlers3::GFXDataType::SaveToFile(std::string location){

	if(this->text != NULL){
		LOGSYSTEM->Log("Saving Text Data...",2);
		this->text->SaveToFile(location);
	}
	if(this->landscape != NULL){
		LOGSYSTEM->Log("Saving Landscapes...",2);
		this->landscape->SaveToFile(location);
	}
	if(this->gui != NULL){
		LOGSYSTEM->Log("Saving GUIs...",2);
		this->gui->SaveToFile(location);
	}
	if(this->object != NULL){
		LOGSYSTEM->Log("Saving Objects...",2);
		this->object->SaveToFile(location);
	}
	if(this->torso != NULL){
		LOGSYSTEM->Log("Saving Torsos...",2);
		this->torso->SaveToFile(location);
	}
	if(this->shadow != NULL){
		LOGSYSTEM->Log("Saving Shadows...",2);
		this->shadow->SaveToFile(location);
	}
	if(this->animation != NULL){
		LOGSYSTEM->Log("Saving Animations...",2);
		this->animation->SaveToFile(location);
	}
	if(this->palette != NULL){
		LOGSYSTEM->Log("Saving Palettes...",2);
		this->palette->SaveToFile(location);
	}
}

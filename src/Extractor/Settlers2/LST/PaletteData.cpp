/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "PaletteData.h"

Extractor::Settlers2::PaletteData::PaletteData(Functions::DataReader* reader){
	this->palette = new RGBA[256];
	for(unsigned int i = 0; i < 256; i++){
		this->palette[i].A = 255;
		this->palette[i].R = reader->ReadChar();
		this->palette[i].G = reader->ReadChar();
		this->palette[i].B = reader->ReadChar();

	}
}

void Extractor::Settlers2::PaletteData::SaveFileData(std::string location){
	std::string data;
	data = Functions::PaletteToText(this->palette);
	std::string filename = location + ".txt";
	Functions::SaveToTextFile(filename,data);

	std::string htmlVersion = "<html>";
	htmlVersion += Functions::PaletteToHtml(this->palette);
	htmlVersion += "</html>";
	Functions::SaveToTextFile(location + ".html",htmlVersion);
}

/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "XMIDIData.h"

void Functions::XMIDIData::SaveFileData(std::string filename){
	if(Functions::FileExists(filename))
		remove(filename.c_str());

	std::ofstream ofile;
	ofile.open(filename.c_str(),std::ios::binary);
	ofile.write((char*)this->data,(length-20));
	ofile.close();
}

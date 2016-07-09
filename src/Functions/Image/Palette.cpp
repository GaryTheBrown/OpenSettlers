/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "Palette.h"

std::string Functions::PaletteToText(RGBA* palette){
	std::string data = "";
	for(int i = 0; i < 256;i++){
		data += "[";
		data += Functions::ToString((unsigned int)palette[i].R);
		data += ",";
		data += Functions::ToString((unsigned int)palette[i].G);
		data += ",";
		data += Functions::ToString((unsigned int)palette[i].B);
		data += ",";
		data += Functions::ToString((unsigned int)palette[i].A);
		data += "]";
	}
	return data;
}

std::string Functions::PaletteToHtml(RGBA* palette){
	std::string htmlVersion = "<table>";
	for(int i = 0; i < 16;i++){
		htmlVersion += "<tr>";
		for(int j = 0; j < 16;j++){
			if (palette[i*16+j].A == 0){//If Transparent
				htmlVersion += "<td>TRANS</td>";
			}else{
				int colour = ((int)palette[i*16+j].R << 16) | ((int)palette[i*16+j].G << 8) | (int)palette[i*16+j].B;
				std::string hex = Functions::ToHex(colour,3);
				std::string textcolour = "#000000";
				if(palette[i*16+j].R < 128 && palette[i*16+j].G < 128 && palette[i*16+j].B < 128)
					textcolour="#FFFFFF";
				htmlVersion += "<td bgcolor=#" + hex + "><font color=" + textcolour + ">" + hex + "</font></td>";
			}
		}
		htmlVersion += "</tr>";
	}
	htmlVersion += "</table>";
	return htmlVersion;
}

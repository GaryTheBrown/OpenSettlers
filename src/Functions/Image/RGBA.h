/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once

class RGBA{
public:
	unsigned char R = 0;
	unsigned char G = 0;
	unsigned char B = 0;
	unsigned char A = 0;

	RGBA(){};
	RGBA(unsigned char R,unsigned char G,unsigned char B,unsigned char A);
	RGBA(short colour, bool c565);
	~RGBA(){};

	unsigned int ReturnInt();
};

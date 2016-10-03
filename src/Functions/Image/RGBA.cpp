/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "RGBA.h"

RGBA::RGBA(unsigned char R,unsigned char G,unsigned char B,unsigned char A)
	:R(R),
	 G(G),
	 B(B),
	 A(A){
}
RGBA::RGBA(short colour, bool c565){
	//- scale Colour from RGB555/RGB565 to RGB888
	//- scale Colour from RGB555 to RGB888 255/248 = 1.02822580645 = USED 1.03
	//- scale Colour from RGB555 to RGB888 255/252 = 1.0119047619  = USED 1.012
	if(c565){
		//565 colour code
		//- scale colours to 255
		this->B = (unsigned char) (1.03 * ((colour << 3) & 0xF8));
		this->G = (unsigned char) (1.012 * ((colour >> 3) & 0xFC));
		this->R = (unsigned char) (1.03 * ((colour >> 8) & 0xF8));
	}
	else{
		// 555 colour code
		//- scale colours to 255
		this->B = (unsigned char) (1.03 * ((colour << 3) & 0xF8));
		this->G = (unsigned char) (1.03 * ((colour >> 2) & 0xF8));
		this->R = (unsigned char) (1.03 * ((colour >> 7) & 0xF8));
	}
	this->A = 255;
}

RGBA::RGBA(unsigned int colour){
	this->R = colour >> 24 & 0xff;
	this->G = colour >> 16 & 0xff;
	this->B = colour >> 8 & 0xff;
	this->A = colour & 0xff;
}

unsigned int RGBA::ReturnInt(){
	return this->R << 24 | this->G << 16 | this->B << 8 | this->A;
}

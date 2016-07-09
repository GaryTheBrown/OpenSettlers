/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "iconv.h"

Functions::iConverter::iConverter(std::string inEncode){
	this->iConv = iconv_open("UTF-8", inEncode.c_str());
}

std::string Functions::iConverter::convert(std::string input){
	// copy the string to a buffer as iconv function requires a non-const char pointer.
	std::vector<char> in_buf(input.begin(), input.end());
	char* src_ptr = &in_buf[0];
	size_t src_size = input.size();

	std::vector<char> buf(input.size()*4);
	std::string output;
	while (0 < src_size){
		char* dst_ptr = &buf[0];
		size_t dst_size = buf.size();

		if (iconv(iConv, &src_ptr, &src_size, &dst_ptr, &dst_size) == (size_t)-1){
			// skip character
			++src_ptr;
			--src_size;
		}
		output.append(&buf[0], buf.size() - dst_size);
	}
	return output;
}

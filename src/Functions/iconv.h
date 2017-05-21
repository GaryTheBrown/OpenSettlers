/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once
#include <iconv.h>
#include <string>
#include <vector>

namespace Functions{
		class iConverter{
		private:
			iconv_t iConv;

		public:
			iConverter(std::string inEncode);
			~iConverter(){iconv_close(iConv);};

			std::string convert(std::string input);
		};
	}

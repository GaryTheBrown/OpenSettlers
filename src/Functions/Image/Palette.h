/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef FUNCTIONS_IMAGE_PALETTE_H
#define FUNCTIONS_IMAGE_PALETTE_H
#include <string>
#include "RGBA.h"
#include "../To.h"

namespace Functions{
	extern std::string PaletteToText(RGBA* palette);
	extern std::string PaletteToHtml(RGBA* palette);
}

#endif
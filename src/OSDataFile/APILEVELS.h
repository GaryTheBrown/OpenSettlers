/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#ifndef OSDATAFILE_APILEVELS_H
#define OSDATAFILE_APILEVELS_H
namespace OSData{
	namespace APILEVEL{
	/*TODO FIGURE OUT A SYSTEM THAT CAN STORE DATA INCASE THE API OF DATA IS LOWER
	 *This may be used by the Converter to also create the data.
	 */
		const unsigned int MASTER = 0;
		const unsigned int MAP = 0;
		const unsigned int ARCHIVE = 0; //Is This one really needed?

		const unsigned int MENULAYOUT = 0;
		const unsigned int LOADINGSCREENLAYOUT = 0;
		const unsigned int GUIITEMS = 0;

		const unsigned int LANDSCAPE = 0;

	}
}

#endif
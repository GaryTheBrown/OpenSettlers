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
#include <stdio.h>
#include <iostream>
#include "Open.h"

namespace Functions{
	class DataReader{
	private:
		unsigned int offset = 0;
		File* file;
		unsigned int hiddenOffset;
		unsigned int blockLength;
		bool endOfFile;

		bool bigEndian = false;

		template <class T> void endswap(T *objp){
		  unsigned char *memp = reinterpret_cast<unsigned char*>(objp);
		  std::reverse(memp, memp + sizeof(T));
		}

	public:
		DataReader(std::string filename, int hiddenOffset = 0, int blockLength = -1);
		~DataReader(){delete this->file;};

		bool EndOfFile(){return this->endOfFile;};
		unsigned int Length(){return this->blockLength;};
		unsigned int FileSize(){return this->file->FileSize();};
		unsigned int GetOffset(){return this->offset;};
		bool SetOffset(unsigned int newOffset);
		bool MoveOffset(signed int value);

		void SetBigEndian(){this->bigEndian = true;};

		char* DirectBufferAccess(unsigned int size, int offset=-1);
		const char* FetchBuffer(int size);

		//Get unsigned Variables
		unsigned char ReadChar();
		unsigned short ReadShort();
		unsigned int ReadInt();
		unsigned long long ReadLongLong();
		std::string ReadString(int size, unsigned int offset);
		//Get signed Variables
		signed short ReadSignedShort();

		std::string FullFileName(){return this->file->FullFileName();};
		std::string FileName(){return this->file->FileName();};
		std::string FileExt(){return this->file->FileExt();};

	};
}

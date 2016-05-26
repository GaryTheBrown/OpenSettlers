/*******************************************************************************
 * Settlers Extractor - A program To extract data file for the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/
#include "SNDHeader.h"
namespace Extractor{
	namespace Settlers3{
		SNDHeader::SNDHeader(Functions::DataReader* reader){
			LOGSYSTEM->Log("Reading:SND:Header...",2);
			reader->SetOffset(0);
			//Header
			this->fileID = reader->ReadInt();
			LOGSYSTEM->Log("Reading:SND:Header:FileID:" + Functions::ToString(this->fileID),3);
			this->version = reader->ReadInt();
			LOGSYSTEM->Log("Reading:SND:Header:Version:" + Functions::ToString(this->version),3);
			this->spacer = reader->ReadInt();
			LOGSYSTEM->Log("Reading:SND:Header:Spacer:" + Functions::ToString(this->spacer),3);
			this->headerSizeA = reader->ReadInt();
			LOGSYSTEM->Log("Reading:SND:Header:HeaderSizeA:" + Functions::ToString(this->headerSizeA),3);
			this->fileSize = reader->ReadInt();
			LOGSYSTEM->Log("Reading:SND:Header:FileSize:" + Functions::ToString(this->fileSize),3);
			this->unknown20 = reader->ReadInt();
			LOGSYSTEM->Log("Reading:SND:Header:Unknown20:" + Functions::ToString(this->unknown20),3);
			this->headerSizeB = reader->ReadInt();
			LOGSYSTEM->Log("Reading:SND:Header:HeaderSizeB:" + Functions::ToString(this->headerSizeB),3);

			//Data Header
			this->headerID = reader->ReadInt();
			LOGSYSTEM->Log("Reading:SND:Data Header:Version:" + Functions::ToString(this->headerID),3);
			this->unknown32 = reader->ReadShort();
			LOGSYSTEM->Log("Reading:SND:Data Header:Unknown32:" + Functions::ToString(this->unknown32),3);
			this->count = reader->ReadShort();
			LOGSYSTEM->Log("Reading:SND:Data Header:Count:" + Functions::ToString(this->count),3);
			unsigned int offsets[this->count];
			LOGSYSTEM->Log("Reading:SND:Data Header:Offsets:",3,false);
			for (unsigned short i = 0;i < this->count;i++){
				offsets[i] = reader->ReadInt();
				LOGSYSTEM->LogCont(Functions::ToString(offsets[i]) + ",",4);
			}
			LOGSYSTEM->newLine(3);

			this->frames = new SNDFrame*[this->count];
			LOGSYSTEM->Log("Reading:SND:Frame:Images:",3,false);
			for (unsigned short i = 0;i < this->count;i++){
				LOGSYSTEM->Log("Reading:SND:Frame:" + Functions::ToString(i),3);
				this->frames[i] = new SNDFrame(reader,offsets[i]);
			}
			LOGSYSTEM->newLine(3);
		}

		SNDHeader::~SNDHeader(){
			for (unsigned short i = 0;i < this->count;i++){
				delete this->frames[i];
			}
			delete[] this->frames;
		}

		void SNDHeader::SaveFileData(std::string location){
			for (unsigned short i = 0;i < this->count;i++){
				if (this->frames[i] != NULL)
					this->frames[i]->SaveFileData(location + "/" + Functions::ToString(i));
			}
		}
	}
}


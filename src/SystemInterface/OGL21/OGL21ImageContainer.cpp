/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "OGL21ImageContainer.h"

SystemInterface::OGL21ImageContainer::OGL21ImageContainer(OGL21System* system){
	this->system = system;
}

SystemInterface::OGL21ImageContainer::OGL21ImageContainer(OGL21System* system, OGL21ImageContainer* imageContainer){
	this->textureID = imageContainer->textureID;
	this->size = imageContainer->size;
	this->location = imageContainer->location;
	this->system = system;
}

SystemInterface::OGL21ImageContainer::~OGL21ImageContainer(){
	//Delete texture
	if(this->textureID != 0){
		glDeleteTextures(1, &this->textureID);
		this->textureID = 0;
	}
}

bool SystemInterface::OGL21ImageContainer::LoadTexture(std::string path){
	if (this->textureID != 0) return false;
	//Load the image from the file into SDL's surface representation
	SDL_Surface* surface = IMG_Load(path.c_str());
	return this->TextureToGPU(surface);
}

bool SystemInterface::OGL21ImageContainer::LoadTexture(Functions::RGBImage* memoryImage){
	if (this->textureID != 0) return false;

    SDL_Surface* surface;

    Uint32 rmask = 0xFF000000;
    Uint32 gmask = 0x00FF0000;
    Uint32 bmask = 0x0000FF00;
    Uint32 amask = 0x000000FF;
    unsigned int size = memoryImage->Width()*memoryImage->Height();
    unsigned char* imageData = new unsigned char[size*4];

   	for (unsigned int i = 0; i < size; i++){
   		imageData[i*4] = memoryImage->ImageRGBA()[i].R;
   		imageData[i*4+1] = memoryImage->ImageRGBA()[i].G;
   		imageData[i*4+2] = memoryImage->ImageRGBA()[i].B;
   		imageData[i*4+3] = memoryImage->ImageRGBA()[i].A;
    }

	surface = SDL_CreateRGBSurfaceFrom(imageData, memoryImage->Width(), memoryImage->Height(), 32, (4*memoryImage->Width()),  rmask, gmask, bmask, amask);
	return this->TextureToGPU(surface);

}
bool SystemInterface::OGL21ImageContainer::CreateTexture(std::pair<int,int> size, RGBA colour){
	if (this->textureID != 0) return false;
	this->size = size;

	SDL_Surface* surface;
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xFF000000;
    gmask = 0x00FF0000;
    bmask = 0x0000FF00;
    amask = 0x000000FF;
#else
    rmask = 0x000000FF;
    gmask = 0x0000FF00;
    bmask = 0x00FF0000;
    amask = 0xFF000000;
#endif
	/* Creating the surface. */
	surface = SDL_CreateRGBSurface(0, size.first, size.second, 32, rmask, gmask, bmask, amask);
	/* Filling the surface with colour. */
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, colour.R, colour.G, colour.B, colour.A));

	return this->TextureToGPU(surface);
}

bool SystemInterface::OGL21ImageContainer::TextToImage(std::string text, RGBA colour, unsigned short fontSize){
	if (this->textureID != 0) return false;
	SDL_Color SDLColour = {colour.B, colour.G, colour.R,255};//This is reversed only here for some reason.
	SDL_Surface* surface = TTF_RenderText_Blended(this->system->fonts->MasterFont(fontSize), text.c_str(), SDLColour);
	this->size = {surface->w,surface->h};
	return this->TextureToGPU(surface);
}

void SystemInterface::OGL21ImageContainer::TextureToScreen(){
	this->TextureToScreen(this->location,this->size);
}

void SystemInterface::OGL21ImageContainer::TextureToScreen(std::pair<int,int> lLocation){
	this->TextureToScreen(lLocation,this->size);
}

void SystemInterface::OGL21ImageContainer::TextureToScreen(std::pair<int,int> lLocation, std::pair<int,int> sSize){
	//If the texture exists
	if(this->textureID != 0){
		//Remove any previous transformations
		glLoadIdentity();

		//Set texture ID
		glBindTexture(GL_TEXTURE_2D, this->textureID);

		//Render textured quad
		glBegin(GL_TRIANGLE_STRIP);//GL_QUADS); last two swapped

			glTexCoord2f(0.f, 0.f); glVertex2i(lLocation.first,lLocation.second);
			glTexCoord2f(1.f, 0.f); glVertex2i(lLocation.first+sSize.first,lLocation.second);
			glTexCoord2f(0.f, 1.f); glVertex2i(lLocation.first,lLocation.second+sSize.second);
			glTexCoord2f(1.f, 1.f); glVertex2i(lLocation.first+sSize.first,lLocation.second+sSize.second);

		glEnd();

	}
}

std::pair<int,int> SystemInterface::OGL21ImageContainer::GetTextureSize(){
	return this->size;
}

bool SystemInterface::OGL21ImageContainer::TextureToGPU(SDL_Surface* surface){
	if (surface==NULL) return false;

	this->size = {surface->w, surface->h};

	//Generate an array of textures.
	glGenTextures(1, &this->textureID);
	//Select (bind) the texture
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	//Specify the texture's data.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE, surface->pixels);
	//Set the minification and magnification filters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
	//Unload SDL's copy of the data; we don't need it anymore because OpenGL now stores it in the texture.
	SDL_FreeSurface(surface);
	return true;
};

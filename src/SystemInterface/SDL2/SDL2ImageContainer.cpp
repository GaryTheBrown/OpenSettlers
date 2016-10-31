/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "SDL2ImageContainer.h"

SystemInterface::SDL2ImageContainer::SDL2ImageContainer(SDL2System* system){
	this->texture = NULL;
	this->system = system;
}

SystemInterface::SDL2ImageContainer::SDL2ImageContainer(SDL2System* system,SDL2ImageContainer* imageContainer){
	this->texture = imageContainer->texture;
	this->sdlRect = imageContainer->sdlRect;
	this->system = system;
}


SystemInterface::SDL2ImageContainer::~SDL2ImageContainer() {
	if(this->texture != NULL)
		SDL_DestroyTexture(this->texture);
}


bool SystemInterface::SDL2ImageContainer::LoadTexture(std::string path){
    if (this->texture != NULL) return false;
	//Load image at specified path
    SDL_Surface* surface = IMG_Load(path.c_str());

    return this->SurfaceToTexture(surface);
};

bool SystemInterface::SDL2ImageContainer::LoadTexture(Functions::RGBImage* memoryImage){
    if (this->texture != NULL) return false;

    SDL_Surface* surface;

    Uint32 rmask = 0x000000FF;
    Uint32 gmask = 0x0000FF00;
    Uint32 bmask = 0x00FF0000;
    Uint32 amask = 0xFF000000;

    unsigned int size = memoryImage->Width()*memoryImage->Height();
    unsigned char* imageData = new unsigned char[size*4];

       	for (unsigned int i = 0; i < size; i++){
       		imageData[i*4] = memoryImage->ImageRGBA()[i].R;
       		imageData[i*4+1] = memoryImage->ImageRGBA()[i].G;
       		imageData[i*4+2] = memoryImage->ImageRGBA()[i].B;
       		imageData[i*4+3] = memoryImage->ImageRGBA()[i].A;
        }

	surface = SDL_CreateRGBSurfaceFrom(imageData, memoryImage->Width(), memoryImage->Height(), 32, 4*memoryImage->Width(),  rmask, gmask, bmask, amask);
	return this->SurfaceToTexture(surface);
}

bool SystemInterface::SDL2ImageContainer::CreateTexture(std::pair<int,int> size, RGBA colour){
	if (this->texture != NULL) return false;
	this->texture = this->system->sdl2Display->SDLCreateTexture(size);

	//transparency
	SDL_SetTextureBlendMode(this->texture,SDL_BLENDMODE_BLEND);

	this->system->sdl2Display->SDLSetRenderTarget(this->texture);
	this->system->sdl2Display->SDLSetRenderDrawColor(colour);
	this->system->sdl2Display->SDLRenderClear();
	this->system->sdl2Display->SDLSetRenderTarget();

    //Get texture size
    SDL_QueryTexture(this->texture, NULL, NULL, &(this->sdlRect.w), &(this->sdlRect.h));

    if (this->texture != NULL) return false;
    return true;
}
bool SystemInterface::SDL2ImageContainer::TextToImage(std::string text, RGBA colour, unsigned short fontSize){
	if (this->texture != NULL) return false;
	SDL_Color SDLColour = {colour.R,colour.G,colour.B,255};

	SDL_Surface* textSurface = TTF_RenderText_Solid(this->system->fonts->MasterFont(fontSize), text.c_str(), SDLColour);
	this->texture = this->system->sdl2Display->SDLCreateTextureFromSurface(textSurface);

	//transparency
	SDL_SetTextureBlendMode(this->texture,SDL_BLENDMODE_BLEND);

    SDL_QueryTexture(this->texture, NULL, NULL, &this->sdlRect.w, &this->sdlRect.h);

    if (this->texture != NULL) return false;
    return true;
}

void SystemInterface::SDL2ImageContainer::TextureToScreen(){
	this->system->sdl2Display->SDLRenderCopy(this->texture, NULL, &this->sdlRect);
}
void SystemInterface::SDL2ImageContainer::TextureToScreen(std::pair<int,int> location){
	SDL_Rect tmplocation = this->sdlRect;
	tmplocation.x = location.first;
	tmplocation.y = location.second;

	this->system->sdl2Display->SDLRenderCopy(this->texture, NULL,  &tmplocation);
}
void SystemInterface::SDL2ImageContainer::TextureToScreen(std::pair<int,int> location, std::pair<int,int> size){
	SDL_Rect tmplocation;
	tmplocation.x = location.first;
	tmplocation.y = location.second;

	if(size.first == 0)
		tmplocation.w = this->sdlRect.w;
	else
		tmplocation.w = size.first;

	if (size.second == 0)
		tmplocation.h = this->sdlRect.h;
	else
		tmplocation.h = size.second;

	this->system->sdl2Display->SDLRenderCopy(this->texture, NULL, &tmplocation);
}

std::pair<int,int> SystemInterface::SDL2ImageContainer::GetTextureSize(){
	std::pair<int,int> size;
	SDL_QueryTexture(this->texture, NULL, NULL, &size.first, &size.second);
	return size;
}

bool SystemInterface::SDL2ImageContainer::SurfaceToTexture(SDL_Surface* surface){
	if (surface==NULL) return false;

	//Create texture from surface pixels
	this->texture = this->system->sdl2Display->SDLCreateTextureFromSurface(surface);

	//transparency
	SDL_SetTextureBlendMode(this->texture,SDL_BLENDMODE_BLEND);

	//Get rid of old loaded surface
	SDL_FreeSurface(surface);

	//Get texture size
	SDL_QueryTexture(this->texture, NULL, NULL, &this->sdlRect.w, &this->sdlRect.h);

	if (this->texture != NULL) return false;
	return true;
}

#include "Resources.h"
#include <stdio.h>

bool Resources::IsAppRunning = true;
int Resources::DeltaTimeMilli = 0;

SDL_Texture* Resources::LoadTexture(std::string fileName, SDL_Renderer* rend)
{
	// Load surface
	SDL_Texture* newTexture = NULL;
	SDL_Surface* tempSurface = SDL_LoadBMP(fileName.c_str());
	if (tempSurface == NULL)
	{
		printf("Unable to load image %s SDL_Error: %s\n",
			fileName.c_str(), SDL_GetError());
		return NULL;
	}

	// Create texture from surface
	newTexture = SDL_CreateTextureFromSurface(rend, tempSurface);
	if (newTexture == NULL)
	{
		printf("Unable to create texture from %s! SDL_Error: %s\n",
			fileName.c_str(), SDL_GetError());
		return NULL;
	}

	// Get rid of tempSurface
	SDL_FreeSurface(tempSurface);

	// Return final!
	return newTexture;
}

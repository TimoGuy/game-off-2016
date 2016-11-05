#pragma once
#include <SDL2/SDL.h>
#include <string>

struct Resources
{
	static bool IsAppRunning;

	static SDL_Texture* LoadTexture(std::string fileName, SDL_Renderer* rend);
};

#include <SDL2/SDL.h>
#include <stdio.h>

// Managing funcs
bool init();
bool loadMedia();
void close();

// The window we'll be rendering to
SDL_Window* window = NULL;

// The surface contained by the window
SDL_Surface* screenSurface = NULL;

// Images
SDL_Surface* sampleImg = NULL;

int main(int argc, char** argv)
{
	printf("Let\'s start!!!\n");

	if (!init())
	{
		printf("Failed to init\n");
		return 1;
	}

	if (!loadMedia())
	{
		printf("Failed to loadMedia\n");
		return 2;
	}

	// Blit image!
	SDL_BlitSurface(sampleImg, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);

	// Wait for test!
	SDL_Delay(2000);

	// End of program
	close();
	return 0;
}

bool init()
{
	// Initialize SDL
	if (SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Create the window
	window = SDL_CreateWindow(
		"SDL Tutorial",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 360,
		SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window wasn\'t created. SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Get window surface
	screenSurface = SDL_GetWindowSurface(window);
	if (screenSurface == NULL)
	{
		printf("screenSurface wasn\'t created. SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Kannpeki!
	return true;
}

bool loadMedia()
{
	// Load splash image
	sampleImg = SDL_LoadBMP("res/img/JojosYolo.bmp");
	if (sampleImg == NULL)
	{
		printf("Unable to load image. SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Yes man!
	return true;
}

void close()
{
	// Unpack
	SDL_FreeSurface(screenSurface);
	screenSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

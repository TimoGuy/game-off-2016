#include <SDL2/SDL.h>
#include <stdio.h>
#include "res/Resources.h"

// Managing funcs
bool init();
bool loadMedia();
void close();

SDL_Window* window = NULL;
SDL_Renderer* screenRenderer = NULL;

// Images
SDL_Texture* sampleImg = NULL;

// Frames per second testing
int ticks = 0;
int frames = 0;
int lastFrameTime = 0;

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

	// Main Event loop
	SDL_Event e;
	while (Resources::IsAppRunning)
	{
		// Handle events
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			// Close button
			case SDL_QUIT:
				Resources::IsAppRunning = false;
				break;

			// Keyboard input
			case SDL_KEYDOWN:
				break;

			case SDL_KEYUP:
				break;
			}
		}

		// Clear screen
		SDL_RenderClear(screenRenderer);

		// Render texture to screen
		SDL_RenderCopy(screenRenderer, sampleImg, NULL, NULL);

		// Update screen
		SDL_RenderPresent(screenRenderer);

		// Update the delta time
		Resources::DeltaTimeMilli = SDL_GetTicks() - lastFrameTime;
		lastFrameTime = SDL_GetTicks();

		// Check the frames per second
		frames++;
		if (SDL_GetTicks() - ticks >= 1000)
		{
			printf("Fps: %d\tMilli: %d\n", frames, Resources::DeltaTimeMilli);
			ticks = SDL_GetTicks();
			frames = 0;
		}
	}

	// End of program
	close();
	return 0;
}

bool init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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

	// Get window renderer
	screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (screenRenderer == NULL)
	{
		printf("screenRenderer wasn\'t created. SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(screenRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Kannpeki!
	return true;
}

bool loadMedia()
{
	// Load splash image
	sampleImg = Resources::LoadTexture("res/img/JojosYolo.bmp", screenRenderer);
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
	SDL_DestroyTexture(sampleImg);
	sampleImg = NULL;

	SDL_DestroyRenderer(screenRenderer);
	SDL_DestroyWindow(window);
	screenRenderer = NULL;
	window = NULL;

	SDL_Quit();

	// Program quit successfully!
	printf("Program ended successfully!\n");
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "res/Resources.h"
#include "events/input/Input.h"
#include "events/input/KeyboardInput.h"
#include "events/EventHandler.h"

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

// Test vars
double w = 0, h = 0;

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

	// Add keyboard
	EventHandler* evh = new KeyboardInput();

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

			// Else
			default:
				evh->HandleEvent(&e);
				break;
			}
		}

		// Update
		double mvSpeed = 1.0 * (double)Resources::DeltaTimeMilli / 10.0;
		// printf("%lf\n", mvSpeed);
		if (Input::KeyStates & K_UP)
		{
			h -= mvSpeed;
		}
		else if (Input::KeyStates & K_DOWN)
		{
			h += mvSpeed;
		}
		else if (Input::KeyStates & K_LEFT)
		{
			w -= mvSpeed;
		}
		else if (Input::KeyStates & K_RIGHT)
		{
			w += mvSpeed;
		}

		SDL_Rect texture_rect;
		texture_rect.x = 0;  //the x coordinate
		texture_rect.y = 0; // the y coordinate
		texture_rect.w = 512 + w; //the width of the texture
		texture_rect.h = 512 + h; //the height of the texture

		// Clear screen
		SDL_RenderClear(screenRenderer);

		// Render texture to screen
		SDL_RenderCopy(screenRenderer, sampleImg, NULL, &texture_rect);

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
	int imgInitFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgInitFlags) & imgInitFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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
	if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear") == SDL_FALSE)
	{
		printf("Linear filter didn\'t load. SDL_Error: %s\n", SDL_GetError());
	}

	// Kannpeki!
	return true;
}

bool loadMedia()
{
	// Load splash image
	// sampleImg = Resources::LoadTexture("res/img/JojosYolo.bmp", screenRenderer);
	sampleImg = Resources::LoadTexture("res/img/landscape-1.jpg", screenRenderer);
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

	IMG_Quit();
	SDL_Quit();

	// Program quit successfully!
	printf("Program ended successfully!\n");
}

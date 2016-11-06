#pragma once
#include <SDL2/SDL.h>

class EventHandler
{
public:
    virtual void HandleEvent(SDL_Event* ev) = 0;
};

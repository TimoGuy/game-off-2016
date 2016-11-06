#pragma once
#include <stdint.h>
#include "../EventHandler.h"

class KeyboardInput : public EventHandler
{
public:
    void HandleEvent(SDL_Event* ev);
private:
    void PressKey(SDL_Event* ev, uint8_t code);
};

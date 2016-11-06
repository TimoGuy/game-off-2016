#include "KeyboardInput.h"
#include "Input.h"

void KeyboardInput::HandleEvent(SDL_Event* ev)
{
    // See if keyboard input was made
    if (ev->type == SDL_KEYDOWN ||
        ev->type == SDL_KEYUP)
    {
        switch (ev->key.keysym.sym)
        {
        case SDLK_a:
        case SDLK_LEFT:
            PressKey(ev, K_LEFT);
            break;

        case SDLK_d:
        case SDLK_RIGHT:
            PressKey(ev, K_RIGHT);
            break;

        case SDLK_w:
        case SDLK_UP:
            PressKey(ev, K_UP);
            break;

        case SDLK_s:
        case SDLK_DOWN:
            PressKey(ev, K_DOWN);
            break;

        case SDLK_x:
        case SDLK_j:
            PressKey(ev, K_BTN1);
            break;

        case SDLK_z:
        case SDLK_k:
            PressKey(ev, K_BTN2);
            break;

        case SDLK_RETURN:
        case SDLK_RETURN2:
            PressKey(ev, K_BTN_RETURN);
            break;
        }
    }
}

void KeyboardInput::PressKey(SDL_Event* ev, uint8_t code)
{
    if (ev->type == SDL_KEYDOWN)
    {
        // Apply bit
        Input::KeyStates = Input::KeyStates | code;
    }
    else if (ev->type == SDL_KEYUP)
    {
        // Remove bit
        Input::KeyStates = Input::KeyStates & ~code;
    }
}

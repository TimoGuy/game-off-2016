#pragma once
#include <stdint.h>

#define K_LEFT 1
#define K_RIGHT 2
#define K_UP 4
#define K_DOWN 8

#define K_BTN1 16
#define K_BTN2 32
#define K_BTN_RETURN 64

struct Input
{
    static uint32_t KeyStates;
};

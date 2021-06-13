#pragma once
#define SDL_MAIN_HANDLED
#ifdef ENABLE_SDL
#ifdef _MSC_VER
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif
#endif
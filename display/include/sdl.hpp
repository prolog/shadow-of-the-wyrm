#pragma once
#define SDL_MAIN_HANDLED
#ifdef ENABLE_SDL
#ifdef _MSC_VER
#include "SDL.h"
#include "SDL_mixer.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#endif
#endif
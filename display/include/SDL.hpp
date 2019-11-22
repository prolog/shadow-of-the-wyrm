#pragma once

#ifdef _MSC_VER
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

// Singleton class used to ensure the SDL functions are properly set up.
class SDL
{
  public:
    void set_up();
    void tear_down();

    bool sdl_color_eq(const SDL_Color& col1, const SDL_Color& col2) const;
};

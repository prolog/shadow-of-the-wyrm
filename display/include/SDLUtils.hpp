#pragma once
#ifdef ENABLE_SDL

#include "sdl.hpp"

class SDLUtils
{
  public:
    bool sdl_color_eq(const SDL_Color& col1, const SDL_Color& col2) const;
};

#endif
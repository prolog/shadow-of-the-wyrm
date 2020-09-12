#pragma once
#ifdef ENABLE_SDL

#include "sdl.hpp"

// Singleton class used to ensure the SDL functions are properly set up.
class SDLInit
{
  public:
    void set_up();
    void tear_down();
};

#endif
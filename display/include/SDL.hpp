#pragma once

// Singleton class used to ensure the SDL functions are properly set up.
class SDL
{
  public:
    void set_up();
    void tear_down();
};

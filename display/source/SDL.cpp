#include <sstream>
#include "Log.hpp"
#include "SDL.h"
#include "SDL.hpp"

using namespace std;

void SDL::set_up()
{
  // Temporary code, will be moved elsewhere once the display is working.
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    ostringstream ss;
    ss << "Unable to initialize SDL: " << SDL_GetError();
    Log::instance().error(ss.str());
  }
}

void SDL::tear_down()
{
  SDL_Quit();
}
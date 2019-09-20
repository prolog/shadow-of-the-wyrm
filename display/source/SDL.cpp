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

bool SDL::sdl_color_eq(const SDL_Color& col1, const SDL_Color& col2) const
{
  bool eq = true;

  eq = eq && (col1.r == col2.r);
  eq = eq && (col1.g == col2.g);
  eq = eq && (col1.b == col2.b);
  eq = eq && (col1.a == col2.a);

  return eq;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDL_test.cpp"
#endif

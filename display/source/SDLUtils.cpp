#include "SDLUtils.hpp"

bool SDLUtils::sdl_color_eq(const SDL_Color& col1, const SDL_Color& col2) const
{
  bool eq = true;

  eq = eq && (col1.r == col2.r);
  eq = eq && (col1.g == col2.g);
  eq = eq && (col1.b == col2.b);
  eq = eq && (col1.a == col2.a);

  return eq;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLUtils_test.cpp"
#endif

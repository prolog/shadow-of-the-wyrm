#ifdef ENABLE_SDL
#include "SDLCursorLocation.hpp"

using namespace std;

SDLCursorLocation::SDLCursorLocation(const int new_total_rows, const int new_total_cols)
: y(0), x(0), total_rows(new_total_rows), total_cols(new_total_cols)
{
}

void SDLCursorLocation::set_yx(const int new_y, const int new_x)
{
  set_y(new_y);
  set_x(new_x);
}

bool SDLCursorLocation::incr()
{
  if ((y == total_rows - 1 && x == total_cols - 1) ||
      (y < 0 || x < 0))
  {
    return false;
  }
  else
  {
    if (x == total_cols - 1)
    {
      x = 0;
      y++;
    }
    else
    {
      x++;
    }

    return true;
  }
}

bool SDLCursorLocation::decr()
{
  if ((y >= total_rows || x >= total_cols) ||
      (y == 0 && x == 0))
  {
    return false;
  }
  else
  {
    if (x == 0)
    {
      x = total_cols - 1;
      y--;
    }
    else
    {
      x--;
    }

    return true;
  }
}

void SDLCursorLocation::reset()
{
  y = 0;
  x = 0;
}

void SDLCursorLocation::set_y(const int new_y)
{
  if (new_y <= total_rows - 1)
  {
    y = new_y;
  }
}

int SDLCursorLocation::get_y() const
{
  return y;
}

void SDLCursorLocation::set_x(const int new_x)
{
  if (new_x <= total_cols - 1)
  {
    x = new_x;
  }
}

int SDLCursorLocation::get_x() const
{
  return x;
}

pair<int, int> SDLCursorLocation::get_yx() const
{
  return {y, x};
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLCursorLocation_test.cpp"
#endif

#endif
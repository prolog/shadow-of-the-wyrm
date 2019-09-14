#include "SDLCursorLocation.hpp"

using namespace std;

SDLCursorLocation::SDLCursorLocation(const int m_y, const int m_x)
: y(0), x(0), max_y(m_y), max_x(m_x)
{
}

bool SDLCursorLocation::incr()
{
  if ((y == max_y || x == max_x) ||
      (y < 0 || x < 0))
  {
    return false;
  }
  else
  {
    if (x == max_x)
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
  if ((y > max_y || x > max_x) ||
      (y == 0 || x == 0))
  {
    return false;
  }
  else
  {
    if (x == 0)
    {
      x = max_x;
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
  if (new_y <= max_y)
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
  if (new_x <= max_x)
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

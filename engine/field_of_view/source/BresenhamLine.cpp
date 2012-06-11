#include <algorithm>
#include <cmath>
#include "BresenhamLine.hpp"

using std::swap;
using std::vector;

vector<Coordinate> BresenhamLine::get_points_in_line(int y1, int x1, int y2, int x2)
{
  vector<Coordinate> coords;
  bool steep = abs(y2 - y1) > abs(x2 - x1);

  if (steep)
  {
    swap(x1, y1);
    swap(x2, y2);
  }

  bool reverse_final_coords = false;

  if (x1 > x2)
  {
    swap(x1, x2);
    swap(y1, y2);
    reverse_final_coords = true;
  }

  int d_x = abs(x2 - x1);
  int d_y = abs(y2 - y1);

  int err = d_x / 2;

  int y = y1;
  int y_inc = (y1 < y2) ? 1 : -1;

  for (int x = x1; x < x2+1; x++)
  {
    Coordinate c;
    
    if (steep)
    {
      c.first = x;
      c.second = y;
    }
    else
    {
      c.first = y;
      c.second = x;
    }
    
    coords.push_back(c);
    
    err -= d_y;

    if (err < 0)
    {
      y += y_inc;
      err += d_x;
    }
  }
  
  if (reverse_final_coords)
  {
    reverse(coords.begin(), coords.end());
  }

  return coords;
}

#ifdef UNIT_TESTS
#include "unit_tests/BresenhamLine_test.cpp"
#endif

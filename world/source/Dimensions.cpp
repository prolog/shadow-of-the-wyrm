#include "Dimensions.hpp"

Dimensions::Dimensions()
{
  // Default dimensions will allow for maps to be displayed on a single
  // screen.
  y = DEFAULT_DIMENSIONS_Y;
  x = DEFAULT_DIMENSIONS_X;
}

Dimensions::Dimensions(const int new_x, const int new_y)
{
  x = new_x;
  y = new_y;
}

void Dimensions::set_x(int new_x)
{
  x = new_x;
}

void Dimensions::set_y(int new_y)
{
  y = new_y;
}

int Dimensions::get_x() const
{
  return x;
}

int Dimensions::get_y() const
{
  return y;
}

void Dimensions::set_depth(const Depth& new_depth)
{
  dim_depth = new_depth;
}

Depth Dimensions::depth() const
{
  return dim_depth;
}

#ifdef UNIT_TESTS
#include "unit_tests/Dimensions_test.cpp"
#endif

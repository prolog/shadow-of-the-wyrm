#include "Dimensions.hpp"
#include "Serialize.hpp"

using namespace std;

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

bool Dimensions::operator==(const Dimensions& d)
{
  bool result = true;

  result = result && (x == d.x);
  result = result && (y == d.y);
  result = result && (dim_depth == d.dim_depth);

  return result;
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

bool Dimensions::serialize(ostream& stream)
{
  Serialize::write_int(stream, y);
  Serialize::write_int(stream, x);
  dim_depth.serialize(stream);

  return true;
}

bool Dimensions::deserialize(istream& stream)
{
  Serialize::read_int(stream, y);
  Serialize::read_int(stream, x);
  dim_depth.deserialize(stream);

  return true;
}

ClassIdentifier Dimensions::internal_class_identifier() const
{
  return CLASS_ID_DIMENSIONS;
}

#ifdef UNIT_TESTS
#include "unit_tests/Dimensions_test.cpp"
#endif

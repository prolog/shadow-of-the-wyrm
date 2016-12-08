#include "BoundingBox.hpp"

using namespace std;

BoundingBox::BoundingBox()
: c1({-1,-1}), c2({-1,-1})
{
}

BoundingBox::BoundingBox(const Coordinate& tl, const Coordinate& br)
: c1(tl), c2(br)
{
}

bool BoundingBox::operator==(const BoundingBox& bb) const
{
  bool result = c1 == bb.c1;
  result = result && c2 == bb.c2;

  return result;
}

Coordinate BoundingBox::get_c1() const
{
  return c1;
}

Coordinate BoundingBox::get_c2() const
{
  return c2;
}

#ifdef UNIT_TESTS
#include "unit_tests/BoundingBox_test.cpp"
#endif


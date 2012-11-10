#include "Boat.hpp"

Boat::Boat()
{
  type = ITEM_TYPE_BOAT;
  symbol = '&';
}

Boat::~Boat()
{
}

Item* Boat::clone()
{
  return new Boat(*this);
}

ClassIdentifier Boat::internal_class_identifier() const
{
  return CLASS_ID_BOAT;
}

#ifdef UNIT_TESTS
#include "unit_tests/Boat_test.cpp"
#endif


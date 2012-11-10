#include "Ring.hpp"

Ring::Ring()
{
  type = ITEM_TYPE_RING;
  symbol = '=';
}

Ring::~Ring()
{
}

Item* Ring::clone()
{
  return new Ring(*this);
}

ClassIdentifier Ring::internal_class_identifier() const
{
  return CLASS_ID_RING;
}

#ifdef UNIT_TESTS
#include "unit_tests/Ring_test.cpp"
#endif


#include "Ring.hpp"

using namespace std;

Ring::Ring()
{
  type = ItemType::ITEM_TYPE_RING;
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
  return ClassIdentifier::CLASS_ID_RING;
}

#ifdef UNIT_TESTS
#include "unit_tests/Ring_test.cpp"
#endif


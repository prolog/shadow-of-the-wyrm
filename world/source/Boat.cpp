#include "Boat.hpp"

using namespace std;

Boat::Boat()
{
  type = ItemType::ITEM_TYPE_BOAT;
  symbol = '&';
}

Boat::~Boat()
{
}

bool Boat::additional_item_attributes_match(ItemPtr item) const
{
  return true;
}

Item* Boat::clone()
{
  return new Boat(*this);
}

ClassIdentifier Boat::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BOAT;
}

#ifdef UNIT_TESTS
#include "unit_tests/Boat_test.cpp"
#endif


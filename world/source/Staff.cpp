#include "Staff.hpp"

using namespace std;

Staff::Staff()
{
  type = ItemType::ITEM_TYPE_STAFF;
  symbol = '|';
}

Staff::~Staff()
{
}

bool Staff::additional_item_attributes_match(ItemPtr item) const
{
  return true;
}

Item* Staff::clone()
{
  return new Staff(*this);
}

ClassIdentifier Staff::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_STAFF;
}

#ifdef UNIT_TESTS
#include "unit_tests/Staff_test.cpp"
#endif


#include "Armour.hpp"

Armour::Armour()
{
  type = ITEM_TYPE_ARMOUR;
  symbol = '[';
}

Armour::~Armour()
{
}

Item* Armour::clone()
{
  return new Armour(*this);
}

ClassIdentifier Armour::internal_class_identifier() const
{
  return CLASS_ID_ARMOUR;
}

#ifdef UNIT_TESTS
#include "unit_tests/Armour_test.cpp"
#endif


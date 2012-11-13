#include "Potion.hpp"

using namespace std;

// Potions will provide a bit of nutrition.
Potion::Potion()
: Consumable(50)
{
  type = ITEM_TYPE_POTION;
  symbol = '!';
}

Potion::~Potion()
{
}

ItemType Potion::get_type() const
{
  return ITEM_TYPE_POTION;
}

Item* Potion::clone()
{
  return new Potion(*this);
}

ClassIdentifier Potion::internal_class_identifier() const
{
  return CLASS_ID_POTION;
}

#ifdef UNIT_TESTS
#include "unit_tests/Potion_test.cpp"
#endif


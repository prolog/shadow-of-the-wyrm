#include "Potion.hpp"

// Potions will provide a bit of nutrition.
Potion::Potion()
: Consumable(50)
{
}

Potion::~Potion()
{
}

ItemType Potion::get_type() const
{
  return ITEM_TYPE_POTION;
}

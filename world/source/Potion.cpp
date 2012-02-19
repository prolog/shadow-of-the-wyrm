#include "Potion.hpp"

// Potions will provide a bit of nutrition.
Potion::Potion()
: Consumable(50)
{
  type = ITEM_TYPE_POTION;
}

Potion::~Potion()
{
}

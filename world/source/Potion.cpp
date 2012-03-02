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

ItemType Potion::get_type() const
{
  return ITEM_TYPE_POTION;
}

uchar Potion::get_symbol() const
{
  return '!';
}

Item* Potion::clone()
{
  return new Potion(*this);
}

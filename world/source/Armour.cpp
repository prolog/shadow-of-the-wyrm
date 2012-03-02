#include "Armour.hpp"

Armour::Armour()
{
  type = ITEM_TYPE_ARMOUR;
}

Armour::~Armour()
{
}

uchar Armour::get_symbol() const
{
  return '[';
}

Item* Armour::clone()
{
  return new Armour(*this);
}

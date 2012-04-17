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

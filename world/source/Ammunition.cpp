#include "Ammunition.hpp"

Ammunition::Ammunition()
{
  type = ITEM_TYPE_AMMUNITION;
  symbol = '/';
}

Ammunition::~Ammunition()
{
}

Item* Ammunition::clone()
{
  return new Ammunition(*this);
}

#include "Ammunition.hpp"

Ammunition::Ammunition()
{
  type = ITEM_TYPE_AMMUNITION;
}

Ammunition::~Ammunition()
{
}

uchar Ammunition::get_symbol() const
{
  return '/';
}

Item* Ammunition::clone()
{
  return new Ammunition(*this);
}

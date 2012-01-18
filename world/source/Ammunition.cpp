#include "Ammunition.hpp"

Ammunition::Ammunition()
{
}

Ammunition::~Ammunition()
{
}

ItemType Ammunition::get_type() const
{
  return ITEM_TYPE_AMMUNITION;
}

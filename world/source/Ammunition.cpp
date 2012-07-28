#include "Ammunition.hpp"

Ammunition::Ammunition()
{
  type = ITEM_TYPE_AMMUNITION;
  symbol = '/';
}

Ammunition::~Ammunition()
{
}

EquipmentWornLocation Ammunition::get_worn_location() const
{
  return EQUIPMENT_WORN_AMMUNITION;
}

Item* Ammunition::clone()
{
  return new Ammunition(*this);
}

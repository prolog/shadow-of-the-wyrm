#include "Boat.hpp"

Boat::Boat()
{
  type = ITEM_TYPE_BOAT;
  symbol = '&';
}

Boat::~Boat()
{
}

Item* Boat::clone()
{
  return new Boat(*this);
}

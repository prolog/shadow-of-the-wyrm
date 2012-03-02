#include "Ring.hpp"

Ring::Ring()
{
  type = ITEM_TYPE_RING;
}

Ring::~Ring()
{
}

uchar Ring::get_symbol() const
{
  return '=';
}

Item* Ring::clone()
{
  return new Ring(*this);
}

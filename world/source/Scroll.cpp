#include "Scroll.hpp"

Scroll::Scroll()
{
  type = ITEM_TYPE_SCROLL;
  symbol = '?';
}

Scroll::~Scroll()
{
}

Item* Scroll::clone()
{
  return new Scroll(*this);
}

#include "Scroll.hpp"

Scroll::Scroll()
{
  type = ITEM_TYPE_SCROLL;
}

Scroll::~Scroll()
{
}

uchar Scroll::get_symbol() const
{
  return '?';
}

Item* Scroll::clone()
{
  return new Scroll(*this);
}

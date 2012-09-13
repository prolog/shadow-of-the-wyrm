#include "Scroll.hpp"

Scroll::Scroll()
{
  type = ITEM_TYPE_SCROLL;
  symbol = '?';
}

Scroll::~Scroll()
{
}

// Scrolls are always gone once read.
bool Scroll::destroy_on_read() const
{
  return true;
}

Item* Scroll::clone()
{
  return new Scroll(*this);
}

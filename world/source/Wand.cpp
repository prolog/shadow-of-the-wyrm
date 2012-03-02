#include "Wand.hpp"

Wand::Wand()
{
  type = ITEM_TYPE_WAND;
}

Wand::~Wand()
{
}

uchar Wand::get_symbol() const
{
  return '\\';
}

Item* Wand::clone()
{
  return new Wand(*this);
}

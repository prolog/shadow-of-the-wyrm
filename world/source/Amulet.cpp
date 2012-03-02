#include "Amulet.hpp"

Amulet::Amulet()
{
  type = ITEM_TYPE_AMULET;
}

Amulet::~Amulet()
{
}

uchar Amulet::get_symbol() const
{
  return '\"';
}

Item* Amulet::clone()
{
  return new Amulet(*this);
}

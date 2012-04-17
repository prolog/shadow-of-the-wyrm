#include "Amulet.hpp"

Amulet::Amulet()
{
  type = ITEM_TYPE_AMULET;
  symbol = '\"';
}

Amulet::~Amulet()
{
}

Item* Amulet::clone()
{
  return new Amulet(*this);
}

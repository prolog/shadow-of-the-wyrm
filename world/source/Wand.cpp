#include "Wand.hpp"

Wand::Wand()
{
  type = ITEM_TYPE_WAND;
  symbol ='\\';
}

Wand::~Wand()
{
}

Item* Wand::clone()
{
  return new Wand(*this);
}

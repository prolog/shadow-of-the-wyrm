#include "MiscItem.hpp"

MiscItem::MiscItem()
{
  type = ITEM_TYPE_MISC;
  symbol = ']';
}

MiscItem::~MiscItem()
{
}

Item* MiscItem::clone()
{
  return new MiscItem(*this);
}

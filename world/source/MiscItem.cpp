#include "MiscItem.hpp"

MiscItem::MiscItem()
{
  type = ITEM_TYPE_MISC;
}

MiscItem::~MiscItem()
{
}

uchar MiscItem::get_symbol() const
{
  return ']';
}

Item* MiscItem::clone()
{
  return new MiscItem(*this);
}

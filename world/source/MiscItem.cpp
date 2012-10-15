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

ClassIdentifier MiscItem::internal_class_identifier() const
{
  return CLASS_ID_MISC_ITEM;
}
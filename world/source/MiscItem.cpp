#include "MiscItem.hpp"

using namespace std;

MiscItem::MiscItem()
{
  type = ItemType::ITEM_TYPE_MISC;
  symbol = ']';
}

MiscItem::~MiscItem()
{
}

bool MiscItem::additional_item_attributes_match(ItemPtr item) const
{
  return true;
}

Item* MiscItem::clone()
{
  return new MiscItem(*this);
}

ClassIdentifier MiscItem::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MISC_ITEM;
}

#ifdef UNIT_TESTS
#include "unit_tests/MiscItem_test.cpp"
#endif


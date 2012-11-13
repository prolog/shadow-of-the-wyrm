#include "MiscItem.hpp"

using namespace std;

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

#ifdef UNIT_TESTS
#include "unit_tests/MiscItem_test.cpp"
#endif


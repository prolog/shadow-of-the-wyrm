#include "Tool.hpp"
#include "ItemProperties.hpp"

using namespace std;

Tool::Tool()
{
  type = ItemType::ITEM_TYPE_TOOL;
  symbol = '(';
}

Tool::~Tool()
{
}

bool Tool::additional_item_attributes_match(ItemPtr item) const
{
  return true;
}

Item* Tool::clone()
{
  return new Tool(*this);
}

ClassIdentifier Tool::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TOOL;
}

bool Tool::serialize(ostream& stream) const
{
  Item::serialize(stream);

  return true;
}

bool Tool::deserialize(istream& stream)
{
  Item::deserialize(stream);

  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/Tool_test.cpp"
#endif


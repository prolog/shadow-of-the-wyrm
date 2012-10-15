#include "Staff.hpp"

Staff::Staff()
{
  type = ITEM_TYPE_STAFF;
  symbol = '|';
}

Staff::~Staff()
{
}

Item* Staff::clone()
{
  return new Staff(*this);
}

ClassIdentifier Staff::internal_class_identifier() const
{
  return CLASS_ID_STAFF;
}

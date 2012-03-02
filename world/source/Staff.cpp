#include "Staff.hpp"

Staff::Staff()
{
  type = ITEM_TYPE_STAFF;
}

Staff::~Staff()
{
}

uchar Staff::get_symbol() const
{
  return '|';
}

Item* Staff::clone()
{
  return new Staff(*this);
}

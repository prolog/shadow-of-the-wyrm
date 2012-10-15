#include "Currency.hpp"

Currency::Currency()
{
  type = ITEM_TYPE_CURRENCY;
  symbol = '$';
}

Currency::~Currency()
{
}

Item* Currency::clone()
{
  return new Currency(*this);
}

ClassIdentifier Currency::internal_class_identifier() const
{
  return CLASS_ID_CURRENCY;
}


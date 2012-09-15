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


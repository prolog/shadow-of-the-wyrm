#include "Currency.hpp"

using namespace std;

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

#ifdef UNIT_TESTS
#include "unit_tests/Currency_test.cpp"
#endif


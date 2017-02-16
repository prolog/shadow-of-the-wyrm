#include "Currency.hpp"

using namespace std;

Currency::Currency()
{
  type = ItemType::ITEM_TYPE_CURRENCY;
  symbol = '$';
  status = ItemStatus::ITEM_STATUS_UNCURSED;
  status_identified = true;
}

Currency::~Currency()
{
}

// Currency is always generated uncursed and shouldn't ever be set to another
// status.
void Currency::set_status(const ItemStatus status_to_ignore)
{
}

void Currency::set_status_identified(const bool new_status_identified)
{
}

bool Currency::additional_item_attributes_match(ItemPtr item) const
{
  return true;
}

Item* Currency::clone()
{
  return new Currency(*this);
}

ClassIdentifier Currency::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CURRENCY;
}

#ifdef UNIT_TESTS
#include "unit_tests/Currency_test.cpp"
#endif


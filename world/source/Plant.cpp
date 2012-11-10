#include "Plant.hpp"

Plant::Plant()
: Consumable(20)
{
  type = ITEM_TYPE_PLANT;
  symbol = 'w';
}

Plant::Plant(const int new_nutrition)
: Consumable(new_nutrition)
{
  type = ITEM_TYPE_PLANT;
  symbol = 'w';
}

Plant::~Plant()
{
}

ItemType Plant::get_type() const
{
  return ITEM_TYPE_PLANT;
}

Item* Plant::clone()
{
  return new Plant(*this);
}

ClassIdentifier Plant::internal_class_identifier() const
{
  return CLASS_ID_PLANT;
}

#ifdef UNIT_TESTS
#include "unit_tests/Plant_test.cpp"
#endif


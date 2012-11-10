#include "Food.hpp"

Food::Food()
: Consumable(100)
{
  type = ITEM_TYPE_FOOD;
  symbol = '%';
}

Food::Food(const int nutr)
: Consumable(nutr)
{
  type = ITEM_TYPE_FOOD;
  symbol = '%';
}

Food::~Food()
{
}

ItemType Food::get_type() const
{
  return ITEM_TYPE_FOOD;
}

Item* Food::clone()
{
  return new Food(*this);
}

ClassIdentifier Food::internal_class_identifier() const
{
  return CLASS_ID_FOOD;
}

#ifdef UNIT_TESTS
#include "unit_tests/Food_test.cpp"
#endif


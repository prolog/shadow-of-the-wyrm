#include "Plant.hpp"

using namespace std;

Plant::Plant()
: Consumable(20,0)
{
  type = ITEM_TYPE_PLANT;
  food_type = FOOD_TYPE_VEGETABLE;
  symbol = 'w';
}

Plant::Plant(const int new_nutrition)
: Consumable(new_nutrition,0)
{
  type = ITEM_TYPE_PLANT;
  food_type = FOOD_TYPE_VEGETABLE;
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
  return ClassIdentifier::CLASS_ID_PLANT;
}

#ifdef UNIT_TESTS
#include "unit_tests/Plant_test.cpp"
#endif


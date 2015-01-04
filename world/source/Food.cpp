#include "Food.hpp"

using namespace std;

Food::Food()
: Consumable(100,0)
{
  type = ItemType::ITEM_TYPE_FOOD;
  symbol = '%';
}

Food::Food(const int nutr)
: Consumable(nutr,0)
{
  type = ItemType::ITEM_TYPE_FOOD;
  symbol = '%';
}

Food::~Food()
{
}

ItemType Food::get_type() const
{
  return ItemType::ITEM_TYPE_FOOD;
}

Item* Food::clone()
{
  return new Food(*this);
}

ClassIdentifier Food::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FOOD;
}

#ifdef UNIT_TESTS
#include "unit_tests/Food_test.cpp"
#endif


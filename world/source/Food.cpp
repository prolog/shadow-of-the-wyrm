#include "Food.hpp"

Food::Food()
: Consumable(100)
{
  type = ITEM_TYPE_FOOD;
}

Food::Food(const int nutr)
: Consumable(nutr)
{
  type = ITEM_TYPE_FOOD;
}

Food::~Food()
{
}

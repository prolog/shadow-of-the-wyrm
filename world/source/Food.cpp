#include "Food.hpp"

Food::Food()
: Consumable(100)
{
}

Food::Food(const int nutr)
: Consumable(nutr)
{
}

Food::~Food()
{
}

ItemType Food::get_type() const
{
  return ITEM_TYPE_FOOD;
}

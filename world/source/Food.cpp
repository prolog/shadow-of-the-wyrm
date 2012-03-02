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

ItemType Food::get_type() const
{
  return ITEM_TYPE_FOOD;
}

uchar Food::get_symbol() const
{
  return '%';
}

Item* Food::clone()
{
  return new Food(*this);
}

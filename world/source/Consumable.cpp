#include "Consumable.hpp"

Consumable::Consumable()
: nutrition(0)
{
}

Consumable::Consumable(const int nutr)
: nutrition(nutr)
{
}

Consumable::~Consumable()
{
}

void Consumable::set_nutrition(const int new_nutrition)
{
  nutrition = new_nutrition;
}

int Consumable::get_nutrition() const
{
  return nutrition;
}

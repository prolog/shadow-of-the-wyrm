#include "FoodCodexDescriber.hpp"
#include "Consumable.hpp"
#include "ItemTypeTextKeys.hpp"

using namespace std;

FoodCodexDescriber::FoodCodexDescriber(ItemPtr item)
: CodexDescriber(item)
{
}

string FoodCodexDescriber::describe_for_synopsis_line() const
{
  ConsumablePtr consumable = dynamic_pointer_cast<Consumable>(item);
  string desc;

  if (consumable != nullptr)
  {
    desc = ItemTypeTextKeys::get_food_type(consumable->get_food_type());
  }

  return desc;
}


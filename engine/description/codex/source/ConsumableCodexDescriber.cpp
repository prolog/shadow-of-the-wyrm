#include <sstream>
#include "ConsumableCodexDescriber.hpp"
#include "Consumable.hpp"
#include "ItemTextKeys.hpp"
#include "ItemTypeTextKeys.hpp"

using namespace std;

ConsumableCodexDescriber::ConsumableCodexDescriber(ConsumablePtr new_consumable)
: CodexDescriber(new_consumable), consumable(new_consumable)
{
}

string ConsumableCodexDescriber::describe_for_synopsis_line() const
{
  string desc;

  if (consumable != nullptr)
  {
    desc = ItemTypeTextKeys::get_food_type(consumable->get_food_type());
  }

  return desc;
}

string ConsumableCodexDescriber::describe_details() const
{
  ostringstream details;

  if (consumable != nullptr)
  {
    details << ItemTextKeys::get_nutrition_message(consumable);

    float std_drinks = consumable->get_standard_drinks();
    if (std_drinks > 0)
    {
      details << " " << ItemTextKeys::get_standard_drinks_message(consumable);
    }
  }

  return details.str();
}

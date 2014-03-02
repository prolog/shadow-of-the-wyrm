#include "ConsumableAction.hpp"
#include "Conversion.hpp"

// Consume a consumable, adding its nutrition to the hunger counter,
// and its grams of absorbable pure alcohol (based on the number of standard 
// drinks) to the creature's grams of unabsorbed alcohol.
ActionCostValue ConsumableAction::consume(CreaturePtr creature, ConsumablePtr consumable)
{
  ActionCostValue action_cost_value = 0;

  if (creature && consumable)
  {
    int nutrition = consumable->get_nutrition();
    HungerClock& hunger = creature->get_hunger_clock_ref();
    hunger.set_hunger(hunger.get_hunger() + nutrition);
    creature->increment_grams_unabsorbed_alcohol(AlcoholConverter::standard_drinks_to_absorbable_grams(consumable->get_standard_drinks()));

    if (nutrition > 0)
    {
      creature->get_conducts_ref().break_conduct(CONDUCT_TYPE_FOODLESS);
    }

    // Vegetarians can't consume meat.
    if (consumable->get_food_type() == FOOD_TYPE_MEAT)
    {
      creature->get_conducts_ref().break_conduct(CONDUCT_TYPE_VEGETARIAN);
    }
  }

  return action_cost_value;
}

ActionCostValue ConsumableAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}


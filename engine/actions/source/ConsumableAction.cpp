#include "ClassManager.hpp"
#include "ConsumableAction.hpp"
#include "Conversion.hpp"
#include "MessageManagerFactory.hpp"
#include "RaceManager.hpp"
#include "ResistancesCalculator.hpp"
#include "StatusEffectFactory.hpp"
#include "StringTable.hpp"

using namespace std;

// Consume a consumable, adding its nutrition to the hunger counter,
// and its grams of absorbable pure alcohol (based on the number of standard 
// drinks) to the creature's grams of unabsorbed alcohol.  Then, check to see
// if it's poisoned - if it is, potentially poison the creature.
ActionCostValue ConsumableAction::consume(CreaturePtr creature, ConsumablePtr consumable)
{
  ActionCostValue action_cost_value = 0;

  if (creature && consumable)
  {
    int nutrition = consumable->get_nutrition();
    HungerClock& hunger = creature->get_hunger_clock_ref();
    hunger.set_hunger(hunger.get_hunger() + nutrition);
    creature->increment_grams_unabsorbed_alcohol(AlcoholConverter::standard_drinks_to_absorbable_grams(consumable->get_standard_drinks()));

    // Get any intrinsics from the resistances on the item being greater than
    // the creature's combined race and class values.
    gain_resistances_from_consumable(creature, consumable);

    if (consumable->get_poisoned())
    {
      // Much greater chance to get poisoned by consuming poisoned food/drink
      // than by getting attacked by a poisoned attack.
      StatusEffectPtr poison = StatusEffectFactory::create_status_effect(StatusIdentifiers::STATUS_ID_POISON);

      if (poison && poison->should_apply_change(creature, ConsumableConstants::FOOD_POISON_APPLICATION_BONUS))
      {
        poison->apply_change(creature);
      }
    }

    if (nutrition > 0)
    {
      creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_FOODLESS);
    }

    // Vegetarians can't consume meat.
    if (consumable->get_food_type() == FoodType::FOOD_TYPE_MEAT)
    {
      creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_VEGETARIAN);
    }
  }

  return action_cost_value;
}

void ConsumableAction::gain_resistances_from_consumable(CreaturePtr creature, ConsumablePtr consumable)
{
  if (creature && consumable)
  {
    ResistancesCalculator rc;
    RaceManager rm;
    ClassManager cm;
    
    Resistances consum_res = consumable->get_resistances();
    Resistances cr_res = rc.calculate_non_equipment_resistances(creature, rm.get_race(creature->get_race_id()), cm.get_class(creature->get_class_id()));
    Resistances& cr_intr = creature->get_intrinsic_resistances_ref();

    bool added_msg = false;

    // For each consumable resistance greater than the creature's resistances,
    // add the delta to the creature's intrinsic resistances, and if the
    // creature is the player, add a message.
    for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
    {
      DamageType dt = static_cast<DamageType>(d);

      ResistancePtr res = consum_res.get_resistance(dt);
      double consum_val = res->get_value();

      double cr_val = cr_res.get_resistance_value(dt);
      double delta = (consum_val - cr_val);

      // Only consider consumable values that are resistances.
      if (consum_val > 0 && delta > 0)
      {
        cr_intr.set_resistance_value(dt, cr_val + delta);
        bool added_new_msg = add_consumable_message_if_necessary(creature, res, delta);

        if (added_new_msg && !added_msg)
        {
          added_msg = true;
        }
      }
    }

    if (added_msg && creature->get_is_player())
    {
      IMessageManager& manager = MessageManagerFactory::instance();
      manager.send();
    }
  }
}

// If the creature is the player, add a message based on the resistance.
bool ConsumableAction::add_consumable_message_if_necessary(CreaturePtr creature, ResistancePtr res, const double delta)
{
  bool added_msg = false;

  // Add a message about the change.
  if (creature && creature->get_is_player() && delta > 0)
  {
    string res_msg = StringTable::get(res->get_gain_message_sid());

    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(res_msg);

    added_msg = true;
  }

  return added_msg;
}

ActionCostValue ConsumableAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}


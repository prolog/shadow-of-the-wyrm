#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "CreatureAlcoholTimer.hpp"
#include "MessageManagerFactory.hpp"
#include "StatusAilmentTextKeys.hpp"

// Check the timer to see if it's time to absorb or metabolize booze.
void CreatureAlcoholTimer::tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature != nullptr)
  {
    uint minutes_for_absorption = alco_calc.calculate_minutes_for_absorption(creature);
    uint minutes_for_metabolization = alco_calc.calculate_minutes_for_metabolization(creature);
    
    bool drunk_before = creature->has_status(StatusIdentifiers::STATUS_ID_DRUNK);

    if (total_minutes_elapsed % minutes_for_absorption == 0)
    {
      absorb_alcohol(creature);
    }

    if (total_minutes_elapsed % minutes_for_metabolization == 0)
    {
      metabolize_alcohol(creature);
    }

    bool drunk_after = creature->has_status(StatusIdentifiers::STATUS_ID_DRUNK);

    add_inebriation_message_if_necessary(creature, drunk_before, drunk_after);
    check_for_alcohol_poisoning_death(creature);
  }
}

// If it's time to absorb alcohol, determine how much unabsorbed alcohol to
// remove from the creature and add to its bloodstream, and modify the
// creature accordingly.
void CreatureAlcoholTimer::absorb_alcohol(CreaturePtr creature)
{
  Blood& blood = creature->get_blood_ref();
  float to_absorb = alco_calc.calculate_grams_to_absorb(creature);

  blood.increment_grams_alcohol(to_absorb);
  creature->decrement_grams_unabsorbed_alcohol(to_absorb);

  if (alco_calc.is_drunk(creature))
  {
    if (!creature->has_status(StatusIdentifiers::STATUS_ID_DRUNK))
    {
      creature->set_status(StatusIdentifiers::STATUS_ID_DRUNK, true);
    }
  }
}

// If it's time to metabolize alcohol, determine how much alcohol should
// be removed from the creature's bloodstream, and modify the creature
// accordingly.
void CreatureAlcoholTimer::metabolize_alcohol(CreaturePtr creature)
{
  Blood& blood = creature->get_blood_ref();
  float to_metabolize = alco_calc.calculate_grams_to_metabolize(creature);
  blood.decrement_grams_alcohol(to_metabolize);

  if (!alco_calc.is_drunk(creature))
  {
    if (creature->has_status(StatusIdentifiers::STATUS_ID_DRUNK))
    {
      creature->remove_status(StatusIdentifiers::STATUS_ID_DRUNK);
    }
  }
}

// Add a message if the creature has become either drunk or sober.
void CreatureAlcoholTimer::add_inebriation_message_if_necessary(CreaturePtr creature, bool drunk_before, bool drunk_after)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  if (drunk_before && !drunk_after)
  {
    if (creature->get_is_player())
    {
      manager.add_new_message(StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SOBER));
    }
    else
    {
      manager.add_new_message(StatusAilmentTextKeys::get_npc_sober_message(creature));
    }
  }
  else if (!drunk_before && drunk_after)
  {
    if (creature->get_is_player())
    {
      manager.add_new_message(StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_DRUNK));
    }
    else
    {
      manager.add_new_message(StatusAilmentTextKeys::get_npc_drunk_message(creature));
    }
  }

  manager.send();
}

// Check to see if a creature has died due to alcohol poisoning
void CreatureAlcoholTimer::check_for_alcohol_poisoning_death(CreaturePtr creature)
{
  if (alco_calc.is_dead_of_alcohol_poisoning(creature))
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    manager.add_new_message(ActionTextKeys::get_alcohol_poisoning_death_message(creature->get_description_sid(), creature->get_is_player()));
    manager.send();

    CombatManager cm;

    CreaturePtr no_attacker;
    cm.deal_damage(no_attacker, creature, creature->get_hit_points().get_current() + 1);
  }
}

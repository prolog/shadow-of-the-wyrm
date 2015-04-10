#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "SlownessCalculator.hpp"
#include "SlownessStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

SlownessStatusEffect::SlownessStatusEffect()
{
  status_calc = std::make_shared<SlownessCalculator>();
}

bool SlownessStatusEffect::after_apply(CreaturePtr creature) const
{
  bool effect_applied = true;

  if (creature)
  {
    // If the creature is hasted, then remove the slow property we've
    // just added, and remove the creature's haste.
    if (creature->has_status(StatusIdentifiers::STATUS_ID_HASTE))
    {
      creature->remove_status(StatusIdentifiers::STATUS_ID_SLOWNESS);

      // Undo the haste status, adding a message if necessary:
      StatusEffectPtr haste = StatusEffectFactory::create_status_effect(StatusIdentifiers::STATUS_ID_HASTE);
      haste->undo_change(creature);

      effect_applied = false;
    }
    else
    {
      // Otherwise:
      //
      // Figure out the haste penalty, and add it to the creature's
      // additional properties so it can be correctly unapplied later.
      //
      // Slowness halves action speed.
      Statistic creature_speed = creature->get_speed();
      int cur_speed = creature_speed.get_current();
      int slowness_modifier = cur_speed;
    
      creature_speed.set_current(cur_speed + slowness_modifier);
      creature->set_speed(creature_speed);

      creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_HASTE_MODIFIER, std::to_string(slowness_modifier));
    }
  }

  return effect_applied;
}

void SlownessStatusEffect::after_undo(CreaturePtr creature) const
{
  if (creature)
  {
    string slow_property = CreatureProperties::CREATURE_PROPERTIES_HASTE_MODIFIER;
    int slowness_modifier = String::to_int(creature->get_additional_property(slow_property));
    Statistic creature_speed = creature->get_speed();
    int cur_speed = creature_speed.get_current();
    
    creature_speed.set_current(cur_speed - slowness_modifier);
    creature->set_speed(creature_speed);

    // Remove the slowness modifier so it can be added next time.
    creature->remove_additional_property(slow_property);
  }
}

string SlownessStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SLOWED);

  return message;
}

string SlownessStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_slowed_message(creature);
  return message;
}

string SlownessStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SLOWNESS_CURED);
  
  return message;
}

string SlownessStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_slowness_message(creature);
  return message;
}

string SlownessStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_SLOWNESS;
}

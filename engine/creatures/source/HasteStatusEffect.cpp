#include <boost/make_shared.hpp>
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "HasteCalculator.hpp"
#include "HasteStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

HasteStatusEffect::HasteStatusEffect()
{
  status_calc = boost::make_shared<HasteCalculator>();
}

bool HasteStatusEffect::after_apply(CreaturePtr creature) const
{
  bool effect_applied = true;

  if (creature)
  {
    // Apply has set the "Haste" flag.  after_apply does two things:
    // - checks to see if there is slowness
    //   (if so, undoes the haste flag, and undoes the slowness)
    // - if no slowness, adds the haste bonus.
    if (creature->has_status(StatusIdentifiers::STATUS_ID_SLOWNESS))
    {
      // Undo haste flag.
      creature->remove_status(StatusIdentifiers::STATUS_ID_HASTE);

      // Undo the slowness, adding a message if necessary:
      StatusEffectPtr slowness = StatusEffectFactory::create_status_effect(StatusIdentifiers::STATUS_ID_SLOWNESS);
      slowness->undo_change(creature);

      effect_applied = false;
    }
    else
    {
      // Figure out the haste bonus, and add it to the creature's
      // additional properties so it can be correctly unapplied later.
      //
      // Slowness halves action speed.
      Statistic creature_speed = creature->get_speed();
      int cur_speed = creature_speed.get_current();
      int haste_modifier = cur_speed / 2;
    
      creature_speed.set_current(cur_speed - haste_modifier);
      creature->set_speed(creature_speed);

      creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_HASTE_MODIFIER, Integer::to_string(haste_modifier));
    }
  }

  return effect_applied;
}

void HasteStatusEffect::after_undo(CreaturePtr creature) const
{
  if (creature)
  {
    string haste_property = CreatureProperties::CREATURE_PROPERTIES_HASTE_MODIFIER;
    int haste_modifier = String::to_int(creature->get_additional_property(haste_property));
    Statistic creature_speed = creature->get_speed();
    int cur_speed = creature_speed.get_current();
    
    creature_speed.set_current(cur_speed + haste_modifier);
    creature->set_speed(creature_speed);

    // Remove the slowness modifier so it can be added next time.
    creature->remove_additional_property(haste_property);
  }
}

string HasteStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_HASTED);

  return message;
}

string HasteStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_HASTE_DONE);
  
  return message;
}

string HasteStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_HASTE;
}

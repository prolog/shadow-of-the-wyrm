#include <boost/make_shared.hpp>
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "SlownessCalculator.hpp"
#include "SlownessStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

SlownessStatusEffect::SlownessStatusEffect()
{
  status_calc = boost::make_shared<SlownessCalculator>();
}

void SlownessStatusEffect::after_apply(CreaturePtr creature) const
{
  if (creature)
  {
    // Figure out the haste penalty, and add it to the creature's
    // additional properties so it can be correctly unapplied later.
    //
    // Slowness halves action speed.
    Statistic creature_speed = creature->get_speed();
    int cur_speed = creature_speed.get_current();
    int slowness_modifier = cur_speed;
    
    creature_speed.set_current(cur_speed + slowness_modifier);
    creature->set_speed(creature_speed);

    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_HASTE_MODIFIER, Integer::to_string(slowness_modifier));
  }
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

string SlownessStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SLOWNESS_CURED);
  
  return message;
}

string SlownessStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_SLOWNESS;
}

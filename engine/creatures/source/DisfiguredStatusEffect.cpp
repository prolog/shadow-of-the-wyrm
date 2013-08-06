#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "DisfiguredCalculator.hpp"
#include "DisfiguredStatusEffect.hpp"
#include "RNG.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

DisfiguredStatusEffect::DisfiguredStatusEffect()
{
  status_calc = boost::make_shared<DisfiguredCalculator>();
}

// After determining that the creature has been disfigured, try each
// statistic to see if it should be reduced.  If none should be reduced,
// remove the status ailment and return false.
bool DisfiguredStatusEffect::after_apply(CreaturePtr creature) const
{
  bool creature_disfigured = false;
  int reduce_amount;

  // Str
  string stat_key = CreatureProperties::CREATURE_PROPERTIES_DISFIG_STR_MOD;
  if (RNG::percent_chance(25))
  {
    Statistic str = creature->get_strength();
    int stat_cur = str.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3);
    str.set_current(stat_cur - reduce_amount);
    creature->set_strength(str);
    creature->set_additional_property(stat_key, Integer::to_string(reduce_amount));
    creature_disfigured = true;
  }

  // Dex
  stat_key = CreatureProperties::CREATURE_PROPERTIES_DISFIG_DEX_MOD;
  if (RNG::percent_chance(25))
  {
    Statistic dex = creature->get_dexterity();
    int stat_cur = dex.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3);
    dex.set_current(stat_cur - reduce_amount);
    creature->set_dexterity(dex);
    creature->set_additional_property(stat_key, Integer::to_string(reduce_amount));
    creature_disfigured = true;
  }

  // Agi
  stat_key = CreatureProperties::CREATURE_PROPERTIES_DISFIG_AGI_MOD;
  if (RNG::percent_chance(25))
  {
    Statistic agi = creature->get_agility();
    int stat_cur = agi.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3);
    agi.set_current(stat_cur - reduce_amount);
    creature->set_agility(agi);
    creature->set_additional_property(stat_key, Integer::to_string(reduce_amount));
    creature_disfigured = true;
  }

  // Hea
  stat_key = CreatureProperties::CREATURE_PROPERTIES_DISFIG_HEA_MOD;
  if (RNG::percent_chance(25))
  {
    Statistic hea = creature->get_health();
    int stat_cur = hea.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3);
    hea.set_current(stat_cur - reduce_amount);
    creature->set_health(hea);
    creature->set_additional_property(stat_key, Integer::to_string(reduce_amount));
    creature_disfigured = true;
  }

  // Int
  stat_key = CreatureProperties::CREATURE_PROPERTIES_DISFIG_INT_MOD;
  if (RNG::percent_chance(25))
  {
    Statistic intl = creature->get_intelligence();
    int stat_cur = intl.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3);
    intl.set_current(stat_cur - reduce_amount);
    creature->set_intelligence(intl);
    creature->set_additional_property(stat_key, Integer::to_string(reduce_amount));
    creature_disfigured = true;
  }

  // Wil
  stat_key = CreatureProperties::CREATURE_PROPERTIES_DISFIG_WIL_MOD;
  if (RNG::percent_chance(25))
  {
    Statistic wil = creature->get_willpower();
    int stat_cur = wil.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3);
    wil.set_current(stat_cur - reduce_amount);
    creature->set_willpower(wil);
    creature->set_additional_property(stat_key, Integer::to_string(reduce_amount));
    creature_disfigured = true;
  }
  
  // Cha
  stat_key = CreatureProperties::CREATURE_PROPERTIES_DISFIG_CHA_MOD;
  if (RNG::percent_chance(25))
  {
    Statistic cha = creature->get_charisma();
    int stat_cur = cha.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3);
    cha.set_current(stat_cur - reduce_amount);
    creature->set_charisma(cha);
    creature->set_additional_property(stat_key, Integer::to_string(reduce_amount));
    creature_disfigured = true;
  }

  if (!creature_disfigured)
  {
    creature->remove_status(get_status_identifier());
  }

  return creature_disfigured;
}

// After the status identifier has been removed from the creature's list,
// iterate through the list of disfigurement properties, and check for them.
// If the creature has the property, update the statistic by the integer amount
// that is the key's value in the additional properties map, and remove the
// property.
void DisfiguredStatusEffect::after_undo(CreaturePtr creature) const
{
  if (creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_STR_MOD))
  {
    Statistic str = creature->get_strength();
    str.set_current(str.get_current() + String::to_int(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_STR_MOD)));
    creature->set_strength(str);
    creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_STR_MOD);
  }

  if (creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_DEX_MOD))
  {
    Statistic dex = creature->get_dexterity();
    dex.set_current(dex.get_current() + String::to_int(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_DEX_MOD)));
    creature->set_dexterity(dex);
    creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_DEX_MOD);
  }

  if (creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_AGI_MOD))
  {
    Statistic agi = creature->get_agility();
    agi.set_current(agi.get_current() + String::to_int(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_AGI_MOD)));
    creature->set_agility(agi);
    creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_AGI_MOD);
  }

  if (creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_HEA_MOD))
  {
    Statistic hea = creature->get_health();
    hea.set_current(hea.get_current() + String::to_int(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_HEA_MOD)));
    creature->set_health(hea);
    creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_HEA_MOD);
  }

  if (creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_INT_MOD))
  {
    Statistic intl = creature->get_intelligence();
    intl.set_current(intl.get_current() + String::to_int(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_INT_MOD)));
    creature->set_intelligence(intl);
    creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_INT_MOD);
  }

  if (creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_WIL_MOD))
  {
    Statistic wil = creature->get_willpower();
    wil.set_current(wil.get_current() + String::to_int(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_WIL_MOD)));
    creature->set_willpower(wil);
    creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_WIL_MOD);
  }

  if (creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_CHA_MOD))
  {
    Statistic cha = creature->get_charisma();
    cha.set_current(cha.get_current() + String::to_int(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_CHA_MOD)));
    creature->set_charisma(cha);
    creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_DISFIG_CHA_MOD);
  }
}

string DisfiguredStatusEffect::get_player_application_message() const
{
  return StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_DISFIGURED);
}

string DisfiguredStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  return StatusAilmentTextKeys::get_npc_disfigured_message(creature);
}

string DisfiguredStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_DISFIGURED_CURED);
  return message;
}

string DisfiguredStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_disfigured_message(creature);

  return message;
}

string DisfiguredStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_DISFIGURED;
}

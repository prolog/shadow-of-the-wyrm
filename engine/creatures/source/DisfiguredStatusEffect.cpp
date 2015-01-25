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
  status_calc = std::make_shared<DisfiguredCalculator>();
}

Modifier DisfiguredStatusEffect::get_base_modifier(CreaturePtr creature) const
{
  Modifier m;

  bool creature_disfigured = false;
  int reduce_amount;

  // Str
  if (RNG::percent_chance(25))
  {
    Statistic str = creature->get_strength();
    int stat_cur = str.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3) * -1;
    m.set_strength_modifier(reduce_amount);
    creature_disfigured = true;
  }

  // Dex
  if (RNG::percent_chance(25))
  {
    Statistic dex = creature->get_dexterity();
    int stat_cur = dex.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3) * -1;
    m.set_dexterity_modifier(reduce_amount);
    creature_disfigured = true;
  }

  // Agi
  if (RNG::percent_chance(25))
  {
    Statistic agi = creature->get_agility();
    int stat_cur = agi.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3) * -1;
    m.set_agility_modifier(reduce_amount);
    creature_disfigured = true;
  }

  // Hea
  if (RNG::percent_chance(25))
  {
    Statistic hea = creature->get_health();
    int stat_cur = hea.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3) * -1;
    m.set_health_modifier(reduce_amount);
    creature_disfigured = true;
  }

  // Int
  if (RNG::percent_chance(25))
  {
    Statistic intl = creature->get_intelligence();
    int stat_cur = intl.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3) * -1;
    m.set_intelligence_modifier(reduce_amount);
    creature_disfigured = true;
  }

  // Wil
  if (RNG::percent_chance(25))
  {
    Statistic wil = creature->get_willpower();
    int stat_cur = wil.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3) * -1;
    m.set_willpower_modifier(reduce_amount);
    creature_disfigured = true;
  }

  // Cha
  if (RNG::percent_chance(25) || !creature_disfigured)
  {
    Statistic cha = creature->get_charisma();
    int stat_cur = cha.get_current();
    reduce_amount = RNG::range(stat_cur / 4, stat_cur / 3) * -1;
    m.set_charisma_modifier(reduce_amount);
    creature_disfigured = true;
  }

  return m;
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

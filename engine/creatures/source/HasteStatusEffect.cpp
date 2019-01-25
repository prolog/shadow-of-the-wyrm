#include "Creature.hpp"
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
  status_calc = std::make_shared<HasteCalculator>();
}

bool HasteStatusEffect::is_negative() const
{
  return false;
}

bool HasteStatusEffect::after_apply(CreaturePtr creature) const
{
  bool effect_applied = true;

  if (creature)
  {
    // Apply has set the "Haste" flag.  after_apply checks to see if there
    // is slowness, and if so, removes it.
    if (creature->has_status(StatusIdentifiers::STATUS_ID_SLOWNESS))
    {
      // Undo haste flag.
      creature->remove_status(StatusIdentifiers::STATUS_ID_HASTE);

      // Undo the slowness, adding a message if necessary:
      StatusEffectPtr slowness = StatusEffectFactory::create_status_effect(StatusIdentifiers::STATUS_ID_SLOWNESS, source_id);
      slowness->undo_change(creature);

      effect_applied = false;
    }
  }

  return effect_applied;
}

Modifier HasteStatusEffect::get_base_modifier(CreaturePtr creature, const int danger_level) const
{
  Modifier m;

  if (creature != nullptr)
  {
    int speed_bonus = creature->get_speed().get_base() / 2;
    m.set_speed_modifier(speed_bonus);
  }

  return m;
}

string HasteStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_HASTED);

  return message;
}

string HasteStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_hasted_message(creature);

  return message;
}

string HasteStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_HASTE_DONE);
  
  return message;
}

string HasteStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_haste_message(creature);

  return message;
}

string HasteStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_HASTE;
}

#ifdef UNIT_TESTS
#include "unit_tests/HasteStatusEffect_test.cpp"
#endif
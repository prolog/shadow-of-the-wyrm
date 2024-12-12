#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "Game.hpp"
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

void SlownessStatusEffect::notify_deities(CreaturePtr initiating, CreaturePtr affected_creature) const
{
  if (initiating != nullptr)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();

    game.get_deity_action_manager_ref().notify_action(initiating, current_map, CreatureActionKeys::ACTION_FREEZE, true);
  }
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
      StatusEffectPtr haste = StatusEffectFactory::create_status_effect(initiating_creature, StatusIdentifiers::STATUS_ID_HASTE, source_id);
      haste->undo_change(creature);

      effect_applied = false;
    }
  }

  return effect_applied;
}

Modifier SlownessStatusEffect::get_base_modifier(CreaturePtr creature, const int /*danger_level*/) const
{
  Modifier m;

  if (creature != nullptr)
  {
    int speed_penalty = (creature->get_speed().get_base() / 2 * -1);
    m.set_speed_modifier(speed_penalty);
  }

  return m;
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

#ifdef UNIT_TESTS
#include "unit_tests/SlownessStatusEffect_test.cpp"
#endif
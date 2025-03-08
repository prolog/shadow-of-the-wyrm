#include "BloodiedCalculator.hpp"
#include "BloodiedStatusEffect.hpp"
#include "Game.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

const int BloodiedStatusEffect::BLOODIED_TO_HIT_PENALTY = -15;

BloodiedStatusEffect::BloodiedStatusEffect()
{
  status_calc = std::make_shared<BloodiedCalculator>();
}

string BloodiedStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLOODIED);
  return message;
}

string BloodiedStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_bloodied_message(creature);

  return message;
}

string BloodiedStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLOODIED_CURED);
  return message;
}

string BloodiedStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_bloodied_message(creature);

  return message;
}

Modifier BloodiedStatusEffect::get_base_modifier(CreaturePtr /*creature*/, const int /*danger_level*/) const
{
  Modifier m;

  m.set_to_hit_modifier(BLOODIED_TO_HIT_PENALTY);

  return m;
}

void BloodiedStatusEffect::notify_deities(CreaturePtr init_creature, CreaturePtr /*affected_creature*/) const
{
  if (init_creature != nullptr)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    game.get_deity_action_manager_ref().notify_action(init_creature, current_map, CreatureActionKeys::ACTION_BLOODLETTING, true);
  }
}

string BloodiedStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_BLOODIED;
}

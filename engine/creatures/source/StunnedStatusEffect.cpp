#include "Game.hpp"
#include "StunnedCalculator.hpp"
#include "StunnedStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

StunnedStatusEffect::StunnedStatusEffect()
{
  status_calc = std::make_shared<StunnedCalculator>();
}

void StunnedStatusEffect::notify_deities(CreaturePtr initiating, CreaturePtr /*affected_creature*/) const
{
  if (initiating != nullptr)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();

    game.get_deity_action_manager_ref().notify_action(initiating, current_map, CreatureActionKeys::ACTION_STUN, true);
  }
}

string StunnedStatusEffect::get_player_application_message() const
{
  return StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STUNNED);
}

string StunnedStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  return StatusAilmentTextKeys::get_npc_stunned_message(creature);
}

string StunnedStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STUNNED_CURED);
  return message;
}

string StunnedStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_stunned_message(creature);

  return message;
}

string StunnedStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_STUNNED;
}

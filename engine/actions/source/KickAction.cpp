#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "KickAction.hpp"

using std::string;

KickAction::KickAction()
{
}

ActionCostValue KickAction::kick(CreaturePtr creature)
{
  if (creature)
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

    CurrentCreatureAbilities cca;

    string kick_msg;
    
    if (cca.can_move(creature))
    {
      Game& game = Game::instance();
      MapPtr current_map = game.get_current_map();

      if (current_map->get_map_type() == MAP_TYPE_WORLD && creature->get_is_player())
      {
        kick_msg = StringTable::get(ActionTextKeys::ACTION_KICK_WORLD_MAP);
        manager.add_new_message(kick_msg);
        manager.send();
      }
    }
    else
    {
    }
  }
  
  return get_action_cost_value(creature);
}

ActionCostValue KickAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}


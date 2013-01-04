#include "ChatManager.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "StringConstants.hpp"

using namespace std;

ChatManager::ChatManager()
{
}

ActionCostValue ChatManager::chat(CreaturePtr creature) const
{
  ActionCostValue action_cost = get_nochat_action_cost_value();
  Game* game = Game::instance();

  if (game && creature)
  {
    MapPtr current_map = game->get_current_map();

    if (MapUtils::adjacent_creature_exists(creature, current_map))
    {
      action_cost = get_action_cost_value();
    }
    else
    {
      // JCD FIXME: Refactor this once the main "if" condition is working
      // and chatting actually works.
      MessageManager* manager = MessageManager::instance();

      if (manager)
      {
        manager->add_new_message(StringTable::get(ActionTextKeys::ACTION_CHAT_NOBODY_NEARBY));
        manager->send();
      }
    }
  }

  return action_cost;
}

ActionCostValue ChatManager::get_action_cost_value() const
{
  return 1;
}

ActionCostValue ChatManager::get_nochat_action_cost_value() const
{
  return 0;
}


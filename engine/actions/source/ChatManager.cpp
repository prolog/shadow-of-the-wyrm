#include <boost/make_shared.hpp>
#include "ChatManager.hpp"
#include "Commands.hpp"
#include "Game.hpp"
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
    bool spoke = false;

    if (MapUtils::adjacent_creature_exists(creature, current_map))
    {
      CreatureAdjacencyMap creature_map = MapUtils::get_adjacent_creatures(current_map, creature);

      if (creature_map.size() == 1)
      {
        CreaturePtr speaking_creature = creature_map.begin()->second;
        spoke = chat_single_creature(speaking_creature);
      }
      else
      {
        spoke = chat_multiple_options(creature, creature_map);
      }

      if (spoke)
      {
        action_cost = get_action_cost_value();
      }
    }
    else
    {
      add_chat_message(ActionTextKeys::ACTION_CHAT_NOBODY_NEARBY);
    }
  }

  return action_cost;
}

// Chat with a single creature.  The "single_creature" parameter is the creature
// that should speak back to the acting creature.
bool ChatManager::chat_single_creature(CreaturePtr speaking_creature) const
{
  bool spoke = false;

  if (speaking_creature)
  {
    string speech_text_sid = speaking_creature->get_speech_text_sid();

    // If a creature doesn't have speech text defined, throw up a generic
    // response.
    if (speech_text_sid.empty())
    {
      speech_text_sid = ActionTextKeys::ACTION_CHAT_NO_RESPONSE;
    }

    add_chat_message(speech_text_sid);
    spoke = true;
  }

  return spoke;
}

// When there are multiple creatures, select a single creature to speak with,
// and then speak with it.
bool ChatManager::chat_multiple_options(CreaturePtr querying_creature, const CreatureAdjacencyMap& creature_map) const
{
  bool spoke = false;

  // Make the creature select a direction.
  CommandFactoryPtr command_factory    = boost::make_shared<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = boost::make_shared<KeyboardCommandMap>();

  // If the creature is the player, inform the player that a direction is needed.
  if (querying_creature->get_is_player())
  {
    add_chat_message(ActionTextKeys::ACTION_GET_DIRECTION);
  }

  // Try to get a direction.  This might fail.
  CommandPtr base_command = querying_creature->get_decision_strategy()->get_decision(querying_creature->get_id(), command_factory, kb_command_map);

  if (base_command)
  {
    // Check to see if it's an actual directional command
    boost::shared_ptr<DirectionalCommand> dcommand;
    dcommand = boost::dynamic_pointer_cast<DirectionalCommand>(base_command);

    if (dcommand)
    {
      // It was an actual directional command.  Check to see if there's
      // a creature in that direction.
      Direction requested_direction = dcommand->get_direction();

      CreatureAdjacencyMap::const_iterator c_it = creature_map.find(requested_direction);
      if (c_it != creature_map.end())
      {
        CreaturePtr speaking_creature = c_it->second;
        spoke = chat_single_creature(speaking_creature);
      }
    }
  }

  return spoke;
}

// Add a chat message to the message area.
void ChatManager::add_chat_message(const string& chat_text_sid) const
{
  MessageManager* manager = MessageManager::instance();

  if (manager)
  {
    manager->add_new_message(StringTable::get(chat_text_sid));
    manager->send();
  }
}

// Chatting with a creature successfully incurs the cost of a turn.
ActionCostValue ChatManager::get_action_cost_value() const
{
  return 1;
}

// Make sure that the turn is not advanced if something went wrong (there were
// multiple creatures and the acting creature selected a totally wrong 
// direction, etc.)
ActionCostValue ChatManager::get_nochat_action_cost_value() const
{
  return 0;
}


#include <boost/make_shared.hpp>
#include "ActionTextKeys.hpp"
#include "ChatAction.hpp"
#include "Commands.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

ChatAction::ChatAction()
{
}

ActionCostValue ChatAction::chat(CreaturePtr creature) const
{
  ActionCostValue action_cost = get_nochat_action_cost_value();
  CurrentCreatureAbilities cca;
  Game& game = Game::instance();

  if (!cca.can_see(creature))
  {
    add_chat_message(creature, ActionTextKeys::ACTION_CHAT_NOBODY_NEARBY);
  }
  else
  {
    if (cca.can_speak(creature, true))
    {
      MapPtr current_map = game.get_current_map();
      bool spoke = false;

      if (MapUtils::adjacent_creature_exists(creature, current_map))
      {
        CreatureDirectionMap creature_map = MapUtils::get_adjacent_creatures(current_map, creature);

        if (creature_map.size() == 1)
        {
          CreaturePtr speaking_creature = creature_map.begin()->second;
          spoke = chat_single_creature(creature, speaking_creature);
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
        add_chat_message(creature, ActionTextKeys::ACTION_CHAT_NOBODY_NEARBY);
      }
    }
  }

  return action_cost;
}

// Chat with a single creature.  The "single_creature" parameter is the creature
// that should speak back to the acting creature.
bool ChatAction::chat_single_creature(CreaturePtr querying_creature, CreaturePtr speaking_creature) const
{
  bool spoke = false;

  if (speaking_creature)
  {
    // Check to see if the creature is quest-granting:
    string chat_script = speaking_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_CHAT_SCRIPT);

    if (!chat_script.empty())
    {
      Game& game = Game::instance();
      ScriptEngine& se = game.get_script_engine_ref();
      se.execute(chat_script);

      spoke = true;
    }
    else
    {
      // If not, go ahead and use the default speech option:
      string speech_text_sid = speaking_creature->get_speech_text_sid();

      // If a creature doesn't have speech text defined, throw up a generic
      // response.
      if (speech_text_sid.empty())
      {
        speech_text_sid = ActionTextKeys::ACTION_CHAT_NO_RESPONSE;
      }

      add_chat_message(querying_creature, speech_text_sid);
      spoke = true;
    }
  }

  return spoke;
}

// When there are multiple creatures, select a single creature to speak with,
// and then speak with it.
bool ChatAction::chat_multiple_options(CreaturePtr querying_creature, const CreatureDirectionMap& creature_map) const
{
  bool spoke = false;

  // Make the creature select a direction.
  CommandFactoryPtr command_factory    = boost::make_shared<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = boost::make_shared<KeyboardCommandMap>();

  // If the creature is the player, inform the player that a direction is needed.
  if (querying_creature->get_is_player())
  {
    add_chat_message(querying_creature, ActionTextKeys::ACTION_GET_DIRECTION);
  }

  // Try to get a direction.  This might fail.
  CommandPtr base_command = querying_creature->get_decision_strategy()->get_nonmap_decision(querying_creature->get_id(), command_factory, kb_command_map, 0);

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

      CreatureDirectionMap::const_iterator c_it = creature_map.find(requested_direction);
      if (c_it != creature_map.end())
      {
        CreaturePtr speaking_creature = c_it->second;
        spoke = chat_single_creature(querying_creature, speaking_creature);
      }
    }
  }

  return spoke;
}

// Add a chat message to the message area.
void ChatAction::add_chat_message(CreaturePtr creature, const string& chat_text_sid) const
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(chat_text_sid));
  manager.send();
}

// Chatting with a creature successfully incurs the cost of a turn.
ActionCostValue ChatAction::get_action_cost_value() const
{
  return 1;
}

// Make sure that the turn is not advanced if something went wrong (there were
// multiple creatures and the acting creature selected a totally wrong 
// direction, etc.)
ActionCostValue ChatAction::get_nochat_action_cost_value() const
{
  return 0;
}


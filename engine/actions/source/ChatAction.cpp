#include "ActionTextKeys.hpp"
#include "ChatAction.hpp"
#include "Commands.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "TextFormatSpecifiers.hpp"

using namespace std;

ChatAction::ChatAction()
{
}

ActionCostValue ChatAction::chat(CreaturePtr creature) const
{
  ActionCostValue action_cost = get_nochat_action_cost_value();
  CurrentCreatureAbilities cca;
  Game& game = Game::instance();

  if (creature != nullptr)
  {
    if (!cca.can_see(creature))
    {
      add_chat_message(creature, ActionTextKeys::ACTION_CHAT_NOBODY_NEARBY);
    }
    else
    {
      // If the creature is timewalking, chatting isn't possible, as all the
      // nearby creatures are frozen in time.
      const CreatureStatusMap statuses = creature->get_statuses();
      auto s_it = statuses.find(StatusIdentifiers::STATUS_ID_TIMEWALK);
      if (s_it != statuses.end() && s_it->second.get_value() == true)
      {
        add_chat_message(creature, ActionTextKeys::ACTION_CHAT_TIMEWALK);
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
              creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_SILENT);
              action_cost = get_action_cost_value(creature);
            }
          }
          else
          {
            add_chat_message(creature, ActionTextKeys::ACTION_CHAT_NOBODY_NEARBY);
          }
        }
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
    Game& game = Game::instance();
    ScriptDetails sd = speaking_creature->get_event_script(CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT);
    TimeOfDayType tod = GameUtils::get_date(game).get_time_of_day();
    string speech_text_sid = speaking_creature->get_speech_text_sid();

    // Set the chat text/scripts to the night ones if defined.
    if (tod == TimeOfDayType::TIME_OF_DAY_NIGHT)
    {
      string night_speech_text_sid = speaking_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_NIGHT_SPEECH_TEXT_SID);

      if (!night_speech_text_sid.empty())
      {
        // Set the night speech text.  If there's a regular chat script, blank
        // that out.  It might get replaced by a night chat script further on,
        // but the "regular" script shouldn't fire if there's TOD-related
        // chat text.
        speech_text_sid = night_speech_text_sid;
        sd.set_script("");
      }

      ScriptDetails sd_night = speaking_creature->get_event_script(CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT_NIGHT);

      if (!sd_night.get_script().empty())
      {
        sd = sd_night;
      }
    }

    string chat_script = sd.get_script();

    if (!chat_script.empty())
    {
      ScriptEngine& se = game.get_script_engine_ref();

      if (RNG::percent_chance(sd.get_chance()))
      {
        map<string, string> args = { {"speaking_creature_id", speaking_creature->get_id()} };
        se.execute(chat_script, args);
        spoke = true;
      }
    }
    else
    {
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
  CommandFactoryPtr command_factory    = std::make_unique<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_unique<KeyboardCommandMap>();

  // If the creature is the player, inform the player that a direction is needed.
  if (querying_creature->get_is_player())
  {
    add_chat_message(querying_creature, ActionTextKeys::ACTION_GET_DIRECTION);
  }

  // Try to get a direction.  This might fail.
  CommandPtr base_command = querying_creature->get_decision_strategy()->get_nonmap_decision(false, querying_creature->get_id(), command_factory.get(), kb_command_map.get(), 0, true);

  if (base_command)
  {
    // Check to see if it's an actual directional command
    DirectionalCommand* dcommand = nullptr;
    dcommand = dynamic_cast<DirectionalCommand*>(base_command.get());

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
  IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
  string chat_text = StringTable::get(chat_text_sid);
  vector<string> chat_texts = String::clean_and_trim(String::split(chat_text, TextFormatSpecifiers::NEW_PARAGRAPH));
  size_t ct_sz = chat_texts.size();

  for (size_t i = 0; i < ct_sz; i++)
  {
    string ct = chat_texts.at(i);
    manager.clear_if_necessary();

    if (i < ct_sz - 1)
    {
      manager.add_new_message_with_pause(ct);
      manager.send();
      creature->get_decision_strategy()->get_confirmation();
    }
    else
    {
      manager.add_new_message(ct);
      manager.send();
    }
  }
}

// Chatting with a creature successfully incurs the cost of a turn.
ActionCostValue ChatAction::get_action_cost_value(CreaturePtr /* creature */) const
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


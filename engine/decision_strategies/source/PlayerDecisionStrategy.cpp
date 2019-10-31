#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "PlayerDecisionStrategy.hpp"
#include "Command.hpp"
#include "CommandFactory.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "KeyboardCommandMap.hpp"
#include "Map.hpp"
#include "Setting.hpp"
#include "TextKeys.hpp"

using namespace std;
using std::tolower;

PlayerDecisionStrategy::PlayerDecisionStrategy(ControllerPtr new_controller)
: DecisionStrategy(new_controller)
{
}

DecisionStrategy* PlayerDecisionStrategy::copy()
{
  return new PlayerDecisionStrategy(*this);
}

// The player's decision is easy: just read a command from the keyboard, and then get a CommandPtr
// based on that keyboard input, the provided KeyboardCommandMapPtr, and the CommandFactoryPtr.
CommandPtr PlayerDecisionStrategy::get_nonmap_decision(const bool reprompt_on_cmd_not_found, const string& creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, int* key_p)
{
  MapPtr nullmap;
  return get_decision(reprompt_on_cmd_not_found, creature_id, command_factory, keyboard_commands, nullmap, key_p);
}

CommandPtr PlayerDecisionStrategy::get_decision(const bool reprompt_on_cmd_not_found, const string& creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map, int* key_p)
{
  // view_map is ignored - keyboard input is used, instead.
  CommandPtr player_command;
  long retry_count = 0;

  // Don't prompt for input if input has been provided.
  bool prompt_for_input = !key_p;

  if (command_factory && keyboard_commands)
  {
    while (!player_command && (reprompt_on_cmd_not_found || retry_count == 0))
    {
      retry_count++;
      int key = -1;

      if (prompt_for_input)
      {
        key = controller->get_char_as_int();
      }
      else
      {
        key = *key_p;
      }

      string command_key_s = keyboard_commands->get_command_type(std::to_string(key));
      player_command = command_factory->create(key, command_key_s);

      // If after processing the input the resultant command is
      // null, ensure that we prompt the next time.
      if (!player_command)
      {
        prompt_for_input = true;
      }
    }
  }

  return player_command;
}

// When the player is presented with a number of something (items to drop, turns to wait, etc.),
// get that number
uint PlayerDecisionStrategy::get_count(const uint max_count)
{
  int count = max_count;
  
  if (controller)
  {
    DisplayPtr display = Game::instance().get_display();
    string selected_count = display->add_message_with_prompt("", Colour::COLOUR_WHITE, false);
    
    if (!selected_count.empty()) 
    {
      try
      {
        count = static_cast<uint>(String::to_int(selected_count));
      }
      // If the user entered a value that isn't a valid int, and isn't "enter" (empty str),
      // default to 0:
      catch(...)
      {
        count = 0;
      }
    }
    // User hit enter: default to maximum
    else
    {
      count = max_count;
    }
  }
  
  return count;
}


// Get confirmation - true or false.  Used for commands that require 
// confirmation, like quitting, saving, or leaving an area.
//
// The confirmation_default_value parameter determines what the default
// should be.  Convention is that the default can be true in cases where
// it makes sense and the action is not dangerous, like switching places.
bool PlayerDecisionStrategy::get_confirmation(const bool confirmation_default_value, const bool require_proper_selection)
{
  bool confirm = confirmation_default_value;

  string confirm_str = StringTable::get(TextKeys::DECISION_CONFIRM_KEY);
  string deny_str = StringTable::get(TextKeys::DECISION_DENY_KEY);
  bool require_uppercase = Game::instance().get_settings_ref().get_setting_as_bool(Setting::CONFIRMATION_REQUIRE_CAPITALIZATION);

  if (require_uppercase)
  {
    boost::to_upper(confirm_str);
    boost::to_upper(deny_str);
  }
  else
  {
    boost::to_lower(confirm_str);
    boost::to_lower(deny_str);
  }

  map<string, bool> key_map = {{confirm_str, true}, {deny_str, false}};
  
  bool keep_checking = true;

  while (keep_checking)
  {
    ostringstream ss;
    ss << (char)controller->get_char_as_int(); // needs to be interpreted as a char!
    string user_input = ss.str();

    // If we require uppercase, don't cast the user's input to lowercase.
    // Instead, keep it as-is, and compare it to the confirm/deny keys.
    if (!require_uppercase)
    {
      boost::to_lower(user_input);
    }

    if (user_input.size())
    {
      bool found_entry = false;
      auto k_it = key_map.find(user_input);

      if (k_it != key_map.end())
      {
        confirm = k_it->second;
        found_entry = true;
      }

      if (found_entry || !require_proper_selection)
      {
        keep_checking = false;
      }
    }
  } 

  return confirm;
}

ClassIdentifier PlayerDecisionStrategy::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_PLAYER_DECISION_STRATEGY;
}

#ifdef UNIT_TESTS
#include "unit_tests/PlayerDecisionStrategy_test.cpp"
#endif



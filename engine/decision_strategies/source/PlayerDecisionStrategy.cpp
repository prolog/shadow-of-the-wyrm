#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "PlayerDecisionStrategy.hpp"
#include "Command.hpp"
#include "CommandFactory.hpp"
#include "Conversion.hpp"
#include "KeyboardCommandMap.hpp"
#include "Map.hpp"

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
CommandPtr PlayerDecisionStrategy::get_decision(const string& creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map)
{
  // view_map is ignored - keyboard input is used, instead.
  CommandPtr player_command;

  if (command_factory && keyboard_commands)
  {
    while (!player_command)
    {
      int key = controller->get_char_as_int();
      string command_key_s = keyboard_commands->get_command_type(Integer::to_string(key));
      player_command = command_factory->create(key, command_key_s);
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
    string selected_count = controller->get_line();
    
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


// Get confirmation - true or false.  Used for commands that require confirmation, like quitting,
// saving, or leaving an area.
bool PlayerDecisionStrategy::get_confirmation()
{
  bool confirm = false;
  string confirm_str = StringTable::get(TextKeys::DECISION_CONFIRM_KEY);
  boost::to_lower(confirm_str);
  
  ostringstream ss;
  ss << (char) controller->get_char_as_int(); // needs to be interpreted as a char!
  string user_input = ss.str();
  boost::to_lower(user_input);
  
  if (confirm_str.size() > 0 && user_input.size() > 0 && (confirm_str.at(0) == user_input.at(0)))
  {
    confirm = true;
  }
  
  return confirm;
}

ClassIdentifier PlayerDecisionStrategy::internal_class_identifier() const
{
  return CLASS_ID_PLAYER_DECISION_STRATEGY;
}

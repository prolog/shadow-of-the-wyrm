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
: controller(new_controller)
{
}

// The player's decision is easy: just read a command from the keyboard, and then get a CommandPtr
// based on that keyboard input.
CommandPtr PlayerDecisionStrategy::get_decision()
{
  CommandPtr player_command;

  while (!player_command)
  {
    int key = controller->get_char_as_int();
    string command_key_s = KeyboardCommandMap::get_command_type(Integer::to_string(key));
    player_command = CommandFactory::create(command_key_s);
  }

  return player_command;
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

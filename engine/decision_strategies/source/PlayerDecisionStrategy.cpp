#include <string>
#include "PlayerDecisionStrategy.hpp"
#include "Command.hpp"
#include "CommandFactory.hpp"
#include "Conversion.hpp"
#include "KeyboardCommandMap.hpp"
#include "Map.hpp"

using namespace std;

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
    char key = controller->get_character();
    string command_key_s = KeyboardCommandMap::get_command_type(Char::to_string(key));
    player_command = CommandFactory::create(command_key_s);
  }

  return player_command;
}

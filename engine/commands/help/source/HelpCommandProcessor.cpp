#include "HelpCommandKeys.hpp"
#include "HelpCommandProcessor.hpp"
#include "HelpCommands.hpp"

using namespace std;

HelpCommandProcessor::HelpCommandProcessor()
{
}

HelpCommandProcessor::~HelpCommandProcessor()
{
}

ActionCostValue HelpCommandProcessor::process(CreaturePtr creature, CommandPtr command)
{
  ActionCostValue process_result = 1;

  if (creature && command)
  {
    string command_name = command->get_name();

    if (command_name == HelpCommandKeys::KEYBINDINGS)
    {
      // JCD FIXME
      int x = 1;
    }
    if (command_name == HelpCommandKeys::EXIT_HELP)
    {
      process_result = -1;
    }
  }

  return process_result;
}

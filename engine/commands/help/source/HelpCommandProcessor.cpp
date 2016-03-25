#include "HelpAction.hpp"
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
  HelpAction ha;

  if (creature && command)
  {
    string command_name = command->get_name();

    if (command_name == HelpCommandKeys::KEYBINDINGS)
    {
      return ha.keybindings();
    }
    else if (command_name == HelpCommandKeys::EXIT_HELP)
    {
      process_result = -1;
    }
    else if (command_name == HelpCommandKeys::INTRODUCTION_ROGUELIKES)
    {
      return ha.introduction_roguelikes();
    }
  }

  return process_result;
}

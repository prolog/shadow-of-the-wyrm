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
    else if (command_name == HelpCommandKeys::SOTW_HISTORY)
    {
      return ha.game_history();
    }
    else if (command_name == HelpCommandKeys::STRATEGY_BASICS)
    {
      return ha.strategy_basics();
    }
    else if (command_name == HelpCommandKeys::CASINO_GAMES)
    {
      return ha.casino_games();
    }
  }

  return process_result;
}

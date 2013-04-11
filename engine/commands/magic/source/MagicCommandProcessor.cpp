#include "MagicCommandKeys.hpp"
#include "MagicCommandProcessor.hpp"
#include "MagicCommands.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"

using namespace std;

MagicCommandProcessor::MagicCommandProcessor()
{
}

MagicCommandProcessor::~MagicCommandProcessor()
{
}

ActionCostValue MagicCommandProcessor::process(CreaturePtr creature, CommandPtr command)
{
  ActionCostValue process_result = 1;

  if (creature && command)
  {
    string command_name = command->get_name();

    if (command_name == MagicCommandKeys::EXIT_MAGIC)
    {
      // Special value that signifies to the spellcasting action to stop looping
      // and exit the spellcasting screen.
      process_result = -1;
    }
  }

  return process_result;
}

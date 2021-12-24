#include "MagicCommandKeys.hpp"
#include "MagicCommandProcessor.hpp"
#include "MagicCommands.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "SpellcastingAction.hpp"

using namespace std;

MagicCommandProcessor::MagicCommandProcessor()
{
}

MagicCommandProcessor::~MagicCommandProcessor()
{
}

ActionCostValue MagicCommandProcessor::process(CreaturePtr creature, Command* command)
{
  ActionCostValue process_result = ActionCostConstants::DEFAULT;

  if (creature && command)
  {
    string command_name = command->get_name();

    if (command_name == MagicCommandKeys::ARCANA)
    {
      SpellcastingAction sa;

      string arcana_id = command->get_custom_value(ArcanaCommand::ARCANA_ID);
      return sa.describe_spell(creature, arcana_id);
    }
    else if (command_name == MagicCommandKeys::EXIT_MAGIC)
    {
      // Special value that signifies to the spellcasting action to stop looping
      // and exit the spellcasting screen.
      process_result = -1;
    }
  }

  return process_result;
}

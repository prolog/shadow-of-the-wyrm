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
  return process_result;
}

#include "TileSelectionCommandProcessor.hpp"

using std::string;
using boost::dynamic_pointer_cast;

TileSelectionCommandProcessor::TileSelectionCommandProcessor()
{
}

TileSelectionCommandProcessor::~TileSelectionCommandProcessor()
{
}

ActionCostValue TileSelectionCommandProcessor::process(CreaturePtr creature, CommandPtr command)
{
  ActionCostValue action_cost = 0;

  if (creature && command)
  {
    string command_name = command->get_name();
    CursorDirectionalCommandPtr cdc = dynamic_pointer_cast<CursorDirectionalCommand>(command);
    
    if (cdc)
    {
      action_cost = process_cursor_directional_command(creature, cdc);
    }
    else
    {
      if (command_name == TileSelectionCommandKeys::CANCEL_TILE_SELECTION)
      {
        return -1;
      }
    }
  }

  return action_cost;
}

ActionCostValue TileSelectionCommandProcessor::process_cursor_directional_command(CreaturePtr creature, CursorDirectionalCommandPtr cursor_command)
{
  ActionCostValue action_cost = 0;

  if (creature && cursor_command)
  {
  }

  return action_cost;
}

#include "Game.hpp"
#include "TileSelectionCommandProcessor.hpp"

using std::string;
using std::pair;
using boost::dynamic_pointer_cast;

TileSelectionCommandProcessor::TileSelectionCommandProcessor()
{
}

TileSelectionCommandProcessor::~TileSelectionCommandProcessor()
{
}

pair<bool, ActionCostValue> TileSelectionCommandProcessor::process(CreaturePtr creature, CommandPtr command, TileSelectionManager* const tsm)
{
  pair<bool, ActionCostValue> result(false, 0);
  
  ActionCostValue action_cost = 1;
  Game* game = Game::instance();

  if (creature && game && command)
  {
    string command_name = command->get_name();
    CursorDirectionalCommandPtr cdc = dynamic_pointer_cast<CursorDirectionalCommand>(command);
    
    if (cdc)
    {
      result = process_cursor_directional_command(creature, cdc, tsm);
    }
    else
    {
      if (command_name == TileSelectionCommandKeys::CANCEL_TILE_SELECTION)
      {
        // Do nothing.  TileSelectionManager handles resetting the cursor,
        // etc.
      }
      else if (command_name == TileSelectionCommandKeys::TARGET_TILE)
      {
        // Return the action cost.  The appropriate function in Game* will
        // regain control, and the target details will be present in the
        // creature's map;
        result.second = action_cost;
        
        // Unlike cancelling, selecting a tile should advance the turn.
      }
    }
  }

  return result;
}

pair<bool, ActionCostValue> TileSelectionCommandProcessor::process_cursor_directional_command(CreaturePtr creature, CursorDirectionalCommandPtr cursor_command, TileSelectionManager* const tsm)
{
  pair<bool, ActionCostValue> result(false, 0);
  
  ActionCostValue action_cost = 0;
  Game* game = Game::instance();

  if (creature && cursor_command && game)
  {
    action_cost = game->actions.select_tile(creature, cursor_command->get_direction(), tsm);
    
    result.first = true;
    result.second = action_cost;
  }

  return result;
}

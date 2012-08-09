#include "Game.hpp"
#include "MapCursor.hpp"
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
  Game* game = Game::instance();

  if (creature && game && command)
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
        MapCursor mc;
        mc.reset_cursor(game->get_current_map());
        
        return -1;
      }
    }
  }

  return action_cost;
}

ActionCostValue TileSelectionCommandProcessor::process_cursor_directional_command(CreaturePtr creature, CursorDirectionalCommandPtr cursor_command)
{
  ActionCostValue action_cost = 0;
  Game* game = Game::instance();

  if (creature && cursor_command && game)
  {
    MapCursor mc;
    MapPtr current_map = game->get_current_map();
    Direction direction = cursor_command->get_direction();
    
    mc.update_cursor_location(current_map, direction);
  }

  return action_cost;
}

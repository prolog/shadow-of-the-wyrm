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
        tsm->remove_target(creature, ATTACK_TYPE_RANGED);
      }
      else if (command_name == TileSelectionCommandKeys::TARGET_TILE)
      {
        AttackType JCD_FIXME_ATTACK_TYPE = ATTACK_TYPE_RANGED;
        if (tsm->is_tile_in_range_and_add_message_if_not(creature, JCD_FIXME_ATTACK_TYPE))
        {
          // Stop selecting, advance turn.
          result.second = action_cost;
        }
        else
        {          
          // Keep selecting, do not advance turn.
          result.first = true;
        }
        
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

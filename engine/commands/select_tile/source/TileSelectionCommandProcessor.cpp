#include "CommandKeys.hpp"
#include "Game.hpp"
#include "PlayerConstants.hpp"
#include "TileSelectionCommandProcessor.hpp"

using std::string;
using std::pair;
using std::dynamic_pointer_cast;

TileSelectionCommandProcessor::TileSelectionCommandProcessor()
{
}

TileSelectionCommandProcessor::~TileSelectionCommandProcessor()
{
}

pair<bool, ActionCostValue> TileSelectionCommandProcessor::process(CreaturePtr creature, CommandPtr command, TileSelectionAction* const tsa)
{
  pair<bool, ActionCostValue> result(false, 0);  
  ActionCostValue action_cost = 1;

  if (creature && command)
  {
    string command_name = command->get_name();
    CursorDirectionalCommandPtr cdc = dynamic_pointer_cast<CursorDirectionalCommand>(command);
    
    if (cdc)
    {
      result = process_cursor_directional_command(creature, cdc, tsa);
    }
    else
    {
      if (command_name == TileSelectionCommandKeys::CANCEL_TILE_SELECTION)
      {
        tsa->remove_target(creature, AttackType::ATTACK_TYPE_RANGED);
      }
      else if (command_name == CommandKeys::BESTIARY)
      {
        result = process_tile_selection_bestiary(creature, tsa);
      }
      else if (command_name == TileSelectionCommandKeys::TARGET_TILE)
      {
        AttackType JCD_FIXME_ATTACK_TYPE = AttackType::ATTACK_TYPE_RANGED;
        if (tsa->is_tile_in_range_and_add_message_if_not(creature, JCD_FIXME_ATTACK_TYPE))
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
      else if (command_name == TileSelectionCommandKeys::TARGET_NEXT_CREATURE)
      {
        result = process_tile_selection_by_creature(creature, SelectCreatureType::SELECT_CREATURE_NEXT, tsa);
      }
      else if (command_name == TileSelectionCommandKeys::TARGET_PREV_CREATURE)
      {
        result = process_tile_selection_by_creature(creature, SelectCreatureType::SELECT_CREATURE_PREVIOUS, tsa);
      }
    }
  }

  return result;
}

pair<bool, ActionCostValue> TileSelectionCommandProcessor::process_cursor_directional_command(CreaturePtr creature, CursorDirectionalCommandPtr cursor_command, TileSelectionAction* const tsa)
{
  pair<bool, ActionCostValue> result(false, 0);
  
  ActionCostValue action_cost = 0;
  Game& game = Game::instance();

  if (creature && cursor_command)
  {
    action_cost = game.actions.select_tile(creature, cursor_command->get_direction(), tsa);
    
    result.first = true;
    result.second = action_cost;
  }

  return result;
}

pair<bool, ActionCostValue> TileSelectionCommandProcessor::process_tile_selection_bestiary(CreaturePtr creature, TileSelectionAction* const tsa)
{
  pair<bool, ActionCostValue> result(false, 0);

  string search_text;
  TilePtr tile = tsa->get_cursor_tile();
  bool ok_to_consult_bestiary = false;

  if (tile)
  {
    CreaturePtr tile_creature = tile->get_creature();
          
    if (tile_creature)
    {
      if (tile_creature->get_is_player())
      {
        // The bestiary contains player information under "player", so use the
        // player creature ID, which is itself just "player".
        search_text = PlayerConstants::PLAYER_CREATURE_ID;
      }
      else
      {
        search_text = StringTable::get(tile_creature->get_short_description_sid());
      }

      ok_to_consult_bestiary = true;
    }
  }

  if (ok_to_consult_bestiary)
  {
    Game& game = Game::instance();
    game.get_action_manager_ref().bestiary(creature, search_text);
  }

  return result;
}

// Pick the next or previous creature in the given creature's view map creature list.
pair<bool, ActionCostValue> TileSelectionCommandProcessor::process_tile_selection_by_creature(CreaturePtr creature, const SelectCreatureType sct, TileSelectionAction* const tsa)
{
  pair<bool, ActionCostValue> result(false, 0);

  ActionCostValue action_cost = 0;
  Game& game = Game::instance();

  if (creature)
  {
    action_cost = game.actions.select_tile(creature, sct, tsa);

    result.first = true;
    result.second = action_cost;
  }

  return result;
}
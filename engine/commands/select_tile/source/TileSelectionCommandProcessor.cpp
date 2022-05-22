#include "CommandKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "Setting.hpp"
#include "TileSelectionCommandProcessor.hpp"

using std::list;
using std::string;
using std::pair;
using std::dynamic_pointer_cast;

TileSelectionCommandProcessor::TileSelectionCommandProcessor()
{
}

TileSelectionCommandProcessor::~TileSelectionCommandProcessor()
{
}

pair<bool, ActionCostValue> TileSelectionCommandProcessor::process(CreaturePtr creature, Command* command, TileSelectionAction* const tsa)
{
  pair<bool, ActionCostValue> result(false, 0);  
  ActionCostValue action_cost = ActionCostConstants::DEFAULT;

  if (creature && command)
  {
    string command_name = command->get_name();
    CursorDirectionalCommand* cdc = dynamic_cast<CursorDirectionalCommand*>(command);
    
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
      else if (command_name == CommandKeys::ITEM_CODEX)
      {
        result = process_tile_selection_item_codex(creature, tsa);
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

pair<bool, ActionCostValue> TileSelectionCommandProcessor::process_cursor_directional_command(CreaturePtr creature, CursorDirectionalCommand* cursor_command, TileSelectionAction* const tsa)
{
  pair<bool, ActionCostValue> result(false, 0);
  
  ActionCostValue action_cost = ActionCostConstants::NO_ACTION;
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
  string search_text;
  TilePtr tile = tsa->get_cursor_tile();
  bool ok_to_consult_bestiary = false;
  CreaturePtr tile_creature;

  if (tile)
  {
    tile_creature = tile->get_creature();
          
    if (tile_creature)
    {
      if (tile_creature->get_is_player())
      {
        // The bestiary contains player information under "player", so use the
        // player creature ID, which is itself just "player".
        search_text = CreatureID::CREATURE_ID_PLAYER;
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
    game.get_action_manager_ref().bestiary(creature, search_text, tile_creature);
  }

  return std::make_pair(Game::instance().get_settings_ref().get_setting_as_bool(Setting::CONTINUE_TILE_SELECTION_AFTER_LOOKUP), 0);
}

pair<bool, ActionCostValue> TileSelectionCommandProcessor::process_tile_selection_item_codex(CreaturePtr creature, TileSelectionAction* const tsa)
{
  string search_text;
  TilePtr tile = tsa->get_cursor_tile();
  bool ok_to_consult_codex = false;
  ItemPtr item;

  if (tile)
  {
    IInventoryPtr items = tile->get_items();

    if (items != nullptr)
    {
      uint count = items->get_items_cref().size();

      if (count == 0)
      {
        // count == 0: silently do nothing
      }
      // count > 1: display the list of items, prompt to select one
      else if (count > 1)
      {
        Game& game = Game::instance();
        list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
        item = game.get_action_manager_ref().inventory(creature, items, no_filter, {}, false, false);
        ok_to_consult_codex = (item != nullptr);
      }
      // count == 1: display the single item on the ground
      else
      {
        item = items->get_items_cref().front();
        ok_to_consult_codex = true;
      }
    }
  }

  if (ok_to_consult_codex)
  {
    Game& game = Game::instance();
    game.get_action_manager_ref().item_codex(creature, item, false);
  }

  return std::make_pair(Game::instance().get_settings_ref().get_setting_as_bool(Setting::CONTINUE_TILE_SELECTION_AFTER_LOOKUP), 0);
}

// Pick the next or previous creature in the given creature's view map creature list.
pair<bool, ActionCostValue> TileSelectionCommandProcessor::process_tile_selection_by_creature(CreaturePtr creature, const SelectCreatureType sct, TileSelectionAction* const tsa)
{
  pair<bool, ActionCostValue> result(false, 0);

  ActionCostValue action_cost = ActionCostConstants::NO_ACTION;
  Game& game = Game::instance();

  if (creature)
  {
    action_cost = game.actions.select_tile(creature, sct, tsa);

    result.first = true;
    result.second = action_cost;
  }

  return result;
}
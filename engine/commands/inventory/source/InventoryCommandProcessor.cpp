#include <ctype.h>
#include "Conversion.hpp"
#include "Game.hpp"
#include "InventoryCommandKeys.hpp"
#include "InventoryCommandProcessor.hpp"
#include "InventoryCommands.hpp"
#include "InventoryKeyboardCommandMap.hpp"
#include "InventoryManager.hpp"
#include "ItemFilterFactory.hpp"
#include "Log.hpp"

using namespace std;

InventoryCommandProcessor::InventoryCommandProcessor()
{
}

InventoryCommandProcessor::~InventoryCommandProcessor()
{
}

bool InventoryCommandProcessor::process(InventoryManager* const inv_manager, const list<IItemFilterPtr>& base_item_filter_list, const DisplayInventoryMap& inventory_display, const vector<string>& item_ids, CreaturePtr creature, IInventoryPtr inv, Command* command, const bool inventory_is_read_only, const bool allow_multiple_item_selection, vector<ItemPtr>& selected_items)
{
  bool process_result = true;

  Game& game = Game::instance();

  if (creature && command)
  {
    string command_name = command->get_name();
    
    if (command_name == InventoryCommandKeys::EXIT_INVENTORY)
    {
      process_result = false;
    }
    else if (command_name == InventoryCommandKeys::CLEAR_FILTER)
    {
      list<IItemFilterPtr> empty_filter = {};

      vector<ItemPtr> items = game.actions.inventory_multiple(creature, inv, base_item_filter_list, empty_filter, inventory_is_read_only, allow_multiple_item_selection);

      for (ItemPtr i : items)
      {
        selected_items.push_back(i);
      }

      process_result = false;
    }
    else if (command_name == InventoryCommandKeys::FILTER_VIEW)
    {
      list<IItemFilterPtr> display_filter;
      int key = command->get_key();

      if (key == InventoryKeyboardCommandMap::FILTER_UNPAID[0])
      {
        display_filter = ItemFilterFactory::create_unpaid_filter();
      }
      else
      {
        display_filter = ItemFilterFactory::create_item_type_filter(command->get_key());
      }

      vector<ItemPtr> items = game.actions.inventory_multiple(creature, inv, base_item_filter_list, display_filter, inventory_is_read_only, allow_multiple_item_selection);

      for (ItemPtr i : items)
      {
        selected_items.push_back(i);
      }

      process_result = false;
    }
    else if (command_name == InventoryCommandKeys::SELECT_ITEM)
    {
      process_result = process_select_item(command, inv, item_ids, inventory_is_read_only, allow_multiple_item_selection, selected_items);
    }
    else if (command_name == InventoryCommandKeys::CODEX)
    {
      if (!item_ids.empty())
      {
        ItemPtr selected_item = inv->get_from_id(item_ids[0]);
        Game::instance().get_action_manager_ref().item_codex(creature, selected_item);

        // Reset the selected item so that, next time around, if the player 
        // exits the screen that item isn't selected.
        selected_items.clear();
      }
    }
  }

  return process_result;
}

bool InventoryCommandProcessor::process_select_item(Command* command, IInventoryPtr inv, const vector<string>& item_ids, const bool inventory_is_read_only, const bool allow_multiple_item_selection, vector<ItemPtr>& selected_items)
{
  bool process_result = true;

  if (!inventory_is_read_only)
  {
    ItemSelectionCommand* selection_command = dynamic_cast<ItemSelectionCommand*>(command);

    if (selection_command && !inventory_is_read_only)
    {
      if (allow_multiple_item_selection)
      {
        for (const string& id : item_ids)
        {
          ItemPtr item = inv->get_from_id(id);

          if (item != nullptr)
          {
            selected_items.push_back(item);
            process_result = false;
          }
        }
      }
      else
      {
        if (!item_ids.empty())
        {
          ItemPtr item = inv->get_from_id(item_ids[0]);

          if (item != nullptr)
          {
            selected_items.push_back(item);
            process_result = false;
          }
        }
      }
    }
  }

  return process_result;
}

// Helper function that should not be needed anywhere else - convert a key selection ('a', 'G', etc)
// into an index in 0, 1, ..., where 'a' or 'A' is 0.
uint InventoryCommandProcessor::convert_keypress_to_item_index(int keypress)
{
  if (keypress >= 'A') return (tolower(keypress) - 'a');
  else return 0;
}

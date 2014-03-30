#include <ctype.h>
#include "Conversion.hpp"
#include "Game.hpp"
#include "InventoryCommandKeys.hpp"
#include "InventoryCommandProcessor.hpp"
#include "InventoryCommands.hpp"
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

bool InventoryCommandProcessor::process(InventoryManager* const inv_manager, const DisplayInventoryMap& inventory_display, const string& item_id, CreaturePtr creature, Inventory& inv, CommandPtr command, const bool inventory_is_read_only, ItemPtr& selected_item)
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
      list<IItemFilterPtr> display_filter = ItemFilterFactory::create_empty_filter();

      ItemPtr item = game.actions.inventory(creature, creature->get_inventory(), display_filter, inventory_is_read_only);

      if (item != nullptr)
      {
        selected_item = item;
      }

      process_result = false;
    }
    else if (command_name == InventoryCommandKeys::FILTER_VIEW)
    {
      list<IItemFilterPtr> display_filter = ItemFilterFactory::create_item_type_filter(command->get_key());

      ItemPtr item = game.actions.inventory(creature, creature->get_inventory(), display_filter, inventory_is_read_only);

      if (item != nullptr)
      {
        selected_item = item;
      }

      process_result = false;
    }
    else if (command_name == InventoryCommandKeys::SELECT_ITEM)
    {
      if (!inventory_is_read_only)
      {
        ItemSelectionCommand* selection_command = dynamic_cast<ItemSelectionCommand*>(command.get());
        
        if (selection_command)
        {
          int key = selection_command->get_key();       
          selected_item = inv.get_from_id(item_id);
          
          if (!inventory_is_read_only && selected_item)
          {
            // We're supposed to select an item, and we've done so,
            // so indicate that we should exit the inventory management.
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

#include <ctype.h>
#include "Conversion.hpp"
#include "Game.hpp"
#include "InventoryCommandKeys.hpp"
#include "InventoryCommandProcessor.hpp"
#include "InventoryCommands.hpp"
#include "InventoryManager.hpp"
#include "Log.hpp"

using std::string;

InventoryCommandProcessor::InventoryCommandProcessor()
{
}

InventoryCommandProcessor::~InventoryCommandProcessor()
{
}

bool InventoryCommandProcessor::process(InventoryManager* const inv_manager, const DisplayInventoryMap& inventory_display, CreaturePtr creature, Inventory& inv, CommandPtr command, const bool inventory_is_read_only, ItemPtr& selected_item)
{
  bool process_result = true;

  Game* game = Game::instance();

  if (game && creature && command)
  {
    string command_name = command->get_name();
    
    if (command_name == InventoryCommandKeys::EXIT_INVENTORY)
    {
      process_result = false;
    }
    else if (command_name == InventoryCommandKeys::CLEAR_FILTER)
    {
      // FIXME
    }
    else if (command_name == InventoryCommandKeys::FILTER_VIEW)
    {
      // FIXME
    }
    else if (command_name == InventoryCommandKeys::NEXT_PAGE)
    {
      // FIXME
    }
    else if (command_name == InventoryCommandKeys::PREVIOUS_PAGE)
    {
      // FIXME
    }
    else if (command_name == InventoryCommandKeys::SELECT_ITEM)
    {
      if (!inventory_is_read_only)
      {
        ItemSelectionCommand* selection_command = dynamic_cast<ItemSelectionCommand*>(command.get());
        
        if (selection_command)
        {
          int key = selection_command->get_key();
          Log::instance()->log("Item selected using key " + Integer::to_string(key));
          
          selected_item = inv_manager->select_item(inv, inventory_display, convert_keypress_to_item_index(key));
          
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

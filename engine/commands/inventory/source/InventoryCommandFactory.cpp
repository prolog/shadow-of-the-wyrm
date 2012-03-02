#include <boost/make_shared.hpp>
#include "InventoryCommands.hpp"
#include "InventoryCommandFactory.hpp"
#include "InventoryCommandKeys.hpp"

using boost::make_shared;

InventoryCommandFactory::InventoryCommandFactory()
{
}

InventoryCommandFactory::~InventoryCommandFactory()
{
}

CommandPtr InventoryCommandFactory::create(const int key, const std::string& command_name)
{
  CommandPtr inventory_command;

  if (command_name == InventoryCommandKeys::EXIT_INVENTORY)
  {
    inventory_command = make_shared<ExitInventoryCommand>();
  }
  else if (command_name == InventoryCommandKeys::CLEAR_FILTER)
  {
    inventory_command = make_shared<InventoryClearFilterCommand>();
  }
  else if (command_name == InventoryCommandKeys::FILTER_VIEW)
  {
    inventory_command = make_shared<InventoryFilterViewCommand>();
  }
  else if (command_name == InventoryCommandKeys::NEXT_PAGE)
  {
    inventory_command = make_shared<InventoryNextPageCommand>();
  }
  else if (command_name == InventoryCommandKeys::PREVIOUS_PAGE)
  {
    inventory_command = make_shared<InventoryPreviousPageCommand>();
  }
  else
  {
    // If the key is in the [a-y][A-Y] range, create a selection command
    if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'))
    {
      inventory_command = make_shared<ItemSelectionCommand>(key);      
    }
  }
  
  return inventory_command;
}

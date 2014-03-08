#include "InventoryCommands.hpp"
#include "InventoryCommandKeys.hpp"

ItemSelectionCommand::ItemSelectionCommand(int key)
: Command(InventoryCommandKeys::SELECT_ITEM, key)
{
}

InventoryClearFilterCommand::InventoryClearFilterCommand(const int key)
: Command(InventoryCommandKeys::CLEAR_FILTER, key)
{
}

InventoryFilterViewCommand::InventoryFilterViewCommand(int key)
: Command(InventoryCommandKeys::FILTER_VIEW, key)
{
}

InventoryNextPageCommand::InventoryNextPageCommand(const int key)
: Command(InventoryCommandKeys::NEXT_PAGE, key)
{
}

InventoryPreviousPageCommand::InventoryPreviousPageCommand(const int key)
: Command(InventoryCommandKeys::PREVIOUS_PAGE, key)
{
}

ExitInventoryCommand::ExitInventoryCommand(const int key)
: Command(InventoryCommandKeys::EXIT_INVENTORY, key)
{
}



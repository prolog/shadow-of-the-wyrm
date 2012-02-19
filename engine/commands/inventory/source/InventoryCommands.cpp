#include "InventoryCommands.hpp"
#include "InventoryCommandKeys.hpp"

ItemSelectionCommand::ItemSelectionCommand()
: Command(InventoryCommandKeys::SELECT_ITEM)
{
}

InventoryClearFilterCommand::InventoryClearFilterCommand()
: Command(InventoryCommandKeys::CLEAR_FILTER)
{
}

InventoryFilterViewCommand::InventoryFilterViewCommand()
: Command(InventoryCommandKeys::FILTER_VIEW)
{
}

InventoryNextPageCommand::InventoryNextPageCommand()
: Command(InventoryCommandKeys::NEXT_PAGE)
{
}

InventoryPreviousPageCommand::InventoryPreviousPageCommand()
: Command(InventoryCommandKeys::PREVIOUS_PAGE)
{
}

ExitInventoryCommand::ExitInventoryCommand()
: Command(InventoryCommandKeys::EXIT_INVENTORY)
{
}



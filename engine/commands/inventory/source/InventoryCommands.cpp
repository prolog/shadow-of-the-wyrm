#include "InventoryCommands.hpp"
#include "InventoryCommandKeys.hpp"

ItemSelectionCommand::ItemSelectionCommand(const int key)
: Command(InventoryCommandKeys::SELECT_ITEM, key)
{
}

InventoryClearFilterCommand::InventoryClearFilterCommand(const int key)
: Command(InventoryCommandKeys::CLEAR_FILTER, key)
{
}

InventoryFilterViewCommand::InventoryFilterViewCommand(const int key)
: Command(InventoryCommandKeys::FILTER_VIEW, key)
{
}

ExitInventoryCommand::ExitInventoryCommand(const int key)
: Command(InventoryCommandKeys::EXIT_INVENTORY, key)
{
}

CodexInventoryCommand::CodexInventoryCommand(const int key)
: Command(InventoryCommandKeys::CODEX, key)
{
}

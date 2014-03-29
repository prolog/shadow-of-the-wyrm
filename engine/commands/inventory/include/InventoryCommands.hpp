#pragma once
#include "Command.hpp"

// Class used for general "an item was selected"
class ItemSelectionCommand : public Command
{
  public:
    ItemSelectionCommand(int key);
};

// Class used to indicate, "clear any existing filters; show all the
// applicable items."
class InventoryClearFilterCommand : public Command
{
  public:
    InventoryClearFilterCommand(int key);
};

// Class used to indicate, "within the current context (show all items,
// show applicable items, etc), display only items of a certain type.
class InventoryFilterViewCommand : public Command
{
  public:
    InventoryFilterViewCommand(const int key);
};

// Class used for exiting the inventory screen.
class ExitInventoryCommand : public Command
{
  public:
    ExitInventoryCommand(int key);
};

#pragma once
#include "Command.hpp"

// Class used for general "an item was selected"
class ItemSelectionCommand : public Command
{
  public:
    ItemSelectionCommand();
};

// Class used to indicate, "clear any existing filters; show all the
// applicable items."
class InventoryClearFilterCommand : public Command
{
  public:
    InventoryClearFilterCommand();
};

// Class used to indicate, "within the current context (show all items,
// show applicable items, etc), display only items of a certain type.
class InventoryFilterViewCommand : public Command
{
  public:
    InventoryFilterViewCommand();
};

// Class used to indicate "show the next page of items, if applicable."
class InventoryNextPageCommand : public Command
{
  public:
    InventoryNextPageCommand();
};

// Class used to indicate "show the previous page of items, if applicable."
class InventoryPreviousPageCommand : public Command
{
  public:
    InventoryPreviousPageCommand();
};

// Class used for exiting the inventory screen.
class ExitInventoryCommand : public Command
{
  public:
    ExitInventoryCommand();
};

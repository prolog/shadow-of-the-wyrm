#pragma once
#include "Creature.hpp"

// A command processor used for inventory processing
class InventoryCommandProcessor
{
  public:
    static bool process(CreaturePtr creature, CommandPtr command, ItemPtr selected_item);

  protected:
    InventoryCommandProcessor();
    ~InventoryCommandProcessor();
};

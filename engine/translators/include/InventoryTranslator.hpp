#pragma once
#include "DisplayItem.hpp"
#include "Inventory.hpp"
#include "ItemTypes.hpp"

class InventoryTranslator
{
  public:
    static DisplayInventoryMap create_display_inventory(Inventory& inv);

  protected:
    InventoryTranslator();
    ~InventoryTranslator();
};

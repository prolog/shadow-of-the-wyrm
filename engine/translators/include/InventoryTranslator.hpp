#pragma once
#include "Creature.hpp"
#include "DisplayItem.hpp"
#include "ItemTypes.hpp"

class InventoryTranslator
{
  public:
    static DisplayInventoryMap create_display_inventory(const CreaturePtr& creature);

  protected:
    static DisplayInventoryMap create_initial_display_inventory_categories();
    
    InventoryTranslator();
    ~InventoryTranslator();
};

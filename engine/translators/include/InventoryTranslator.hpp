#pragma once
#include <map>
#include <vector>
#include "Creature.hpp"
#include "DisplayItem.hpp"
#include "ItemTypes.hpp"

typedef std::map<ItemType, std::vector<DisplayItem> > DisplayInventoryMap;

class InventoryTranslator
{
  public:
    static DisplayInventoryMap create_display_inventory(const CreaturePtr& creature);

  protected:
    InventoryTranslator();
    ~InventoryTranslator();
};

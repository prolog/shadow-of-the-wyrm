#pragma once
#include <list>
#include "Creature.hpp"
#include "DisplayItem.hpp"
#include "IInventory.hpp"
#include "ItemTypes.hpp"
#include "IItemFilter.hpp"

class InventoryTranslator
{
  public:
    static DisplayInventoryMap create_display_inventory(CreaturePtr creature, IInventoryPtr inv, const std::list<IItemFilterPtr>& display_filter_list);

  protected:
    static bool is_applicable_for_display(ItemPtr item, const std::list<IItemFilterPtr>& display_filter_list);

    InventoryTranslator();
    ~InventoryTranslator();
};

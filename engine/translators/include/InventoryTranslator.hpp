#pragma once
#include <list>
#include "DisplayItem.hpp"
#include "Inventory.hpp"
#include "ItemTypes.hpp"
#include "IItemDisplayFilter.hpp"

class InventoryTranslator
{
  public:
    static DisplayInventoryMap create_display_inventory(Inventory& inv, const std::list<IItemDisplayFilterPtr>& display_filter_list);

  protected:
    static bool is_applicable_for_display(ItemPtr item, const std::list<IItemDisplayFilterPtr>& display_filter_list);

    InventoryTranslator();
    ~InventoryTranslator();
};

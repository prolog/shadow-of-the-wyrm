#pragma once
#include "DisplayItem.hpp"
#include "Inventory.hpp"
#include "ItemTypes.hpp"

class InventoryTranslator
{
  public:
    static DisplayInventoryMap create_display_inventory(Inventory& inv, const EquipmentWornLocation ewl);

  protected:
    static bool is_applicable_for_display(const EquipmentWornLocation slot_location, const EquipmentWornLocation item_ewl, const bool allow_squishy_filter);
    static bool check_squishy(const EquipmentWornLocation slot_location, const EquipmentWornLocation item_ewl);

    InventoryTranslator();
    ~InventoryTranslator();
};

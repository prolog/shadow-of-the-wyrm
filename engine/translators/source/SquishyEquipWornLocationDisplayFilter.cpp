#include "SquishyEquipWornLocationDisplayFilter.hpp"

SquishyEquipWornLocationDisplayFilter::SquishyEquipWornLocationDisplayFilter(const EquipmentWornLocation ewl)
: slot_location(ewl)
{
}

bool SquishyEquipWornLocationDisplayFilter::passes_filter(ItemPtr item) const
{
  bool pass = false;
  
  if (item)
  {
    EquipmentWornLocation item_ewl = item->get_worn_location();
    
    bool squishy_ring  = ((slot_location == EQUIPMENT_WORN_RIGHT_FINGER) || (slot_location == EQUIPMENT_WORN_LEFT_FINGER));
    bool item_ring     = ((item_ewl == EQUIPMENT_WORN_RIGHT_FINGER) || (item_ewl == EQUIPMENT_WORN_LEFT_FINGER));

    bool squishy_wield = ((slot_location == EQUIPMENT_WORN_WIELDED) || (slot_location == EQUIPMENT_WORN_OFF_HAND) || (slot_location == EQUIPMENT_WORN_AMMUNITION));
    bool item_wield    = ((item_ewl == EQUIPMENT_WORN_WIELDED) || (item_ewl == EQUIPMENT_WORN_OFF_HAND) || (item_ewl == EQUIPMENT_WORN_AMMUNITION));

    pass = ((item_ewl == slot_location) || (squishy_ring && item_ring) || (squishy_wield && item_wield));
  }

  return pass;
}

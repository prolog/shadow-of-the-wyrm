#include "SquishyEquipWornLocationFilter.hpp"

SquishyEquipWornLocationFilter::SquishyEquipWornLocationFilter(const EquipmentWornLocation ewl)
: slot_location(ewl)
{
}

bool SquishyEquipWornLocationFilter::passes_filter(ItemPtr item) const
{
  if (item)
  {
    EquipmentWornLocation ewl = item->get_worn_location();
    return (passes_slot_equality(ewl) || passes_squishy_ring_comparison(ewl) || passes_squishy_wield_comparison(ewl));
  }

  return false;
}

// Check to see if the two worn locations are exactly equal.
bool SquishyEquipWornLocationFilter::passes_slot_equality(const EquipmentWornLocation ewl) const
{
  return (ewl == slot_location);
}

// Check to see if the two worn locations are both ring slots.
bool SquishyEquipWornLocationFilter::passes_squishy_ring_comparison(const EquipmentWornLocation ewl) const
{
  bool squishy_ring  = ((slot_location == EQUIPMENT_WORN_RIGHT_FINGER) || (slot_location == EQUIPMENT_WORN_LEFT_FINGER));
  bool item_ring     = ((ewl == EQUIPMENT_WORN_RIGHT_FINGER) || (ewl == EQUIPMENT_WORN_LEFT_FINGER));
  
  return (squishy_ring && item_ring);
}

// Check to see if the two worn locations are both wield slots.
bool SquishyEquipWornLocationFilter::passes_squishy_wield_comparison(const EquipmentWornLocation ewl) const
{
  bool squishy_wield = ((slot_location == EQUIPMENT_WORN_WIELDED) || (slot_location == EQUIPMENT_WORN_OFF_HAND) || (slot_location == EQUIPMENT_WORN_AMMUNITION));
  bool item_wield    = ((ewl == EQUIPMENT_WORN_WIELDED) || (ewl == EQUIPMENT_WORN_OFF_HAND) || (ewl == EQUIPMENT_WORN_AMMUNITION));
 
  return (item_wield && squishy_wield);
}

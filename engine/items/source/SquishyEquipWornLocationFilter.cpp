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
    ItemType item_type = item->get_type();

    return (passes_slot_equality(ewl) || passes_squishy_ring_comparison(ewl) || passes_squishy_wield_comparison(ewl, item_type));
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
  bool squishy_ring = ((slot_location == EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER) || (slot_location == EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER));
  bool item_ring = ((ewl == EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER) || (ewl == EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER));
  
  return (squishy_ring && item_ring);
}

// Check to see if the two worn locations are both wield slots.
bool SquishyEquipWornLocationFilter::passes_squishy_wield_comparison(const EquipmentWornLocation ewl, const ItemType item_type) const
{
  bool squishy_wield = ((slot_location == EquipmentWornLocation::EQUIPMENT_WORN_WIELDED) || (slot_location == EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND) || (slot_location == EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION));
  bool item_wield = ((ewl == EquipmentWornLocation::EQUIPMENT_WORN_WIELDED && slot_location != EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION) || 
                     (ewl == EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND && slot_location != EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION) ||
                     (slot_location == EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION && 
                       (item_type == ItemType::ITEM_TYPE_AMMUNITION || 
                        item_type == ItemType::ITEM_TYPE_WEAPON || 
                        item_type == ItemType::ITEM_TYPE_POTION)));
 
  return (item_wield && squishy_wield);
}

#ifdef UNIT_TESTS
#include "unit_tests/SquishyEquipWornLocationFilter_test.cpp"
#endif

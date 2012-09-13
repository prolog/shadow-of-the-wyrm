#pragma once
#include "IItemFilter.hpp"

// This class checks to see whether an item can be equipped in a particular
// slot.  It is not strict, and allows squishiness, so if an item specifies
// wielded, it can also be equipped in the offhand.  Similarly, if an item
// specifies "left ring", it can also be equipped as the "right ring".
class SquishyEquipWornLocationFilter : public IItemFilter
{
  public:
    SquishyEquipWornLocationFilter(const EquipmentWornLocation ewl);

    bool passes_filter(ItemPtr item) const;

  protected:
    bool passes_slot_equality(const EquipmentWornLocation ewl) const;
    bool passes_squishy_ring_comparison(const EquipmentWornLocation ewl) const;
    bool passes_squishy_wield_comparison(const EquipmentWornLocation ewl) const;
  
    EquipmentWornLocation slot_location;
};

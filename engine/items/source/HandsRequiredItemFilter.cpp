#include "HandsRequiredItemFilter.hpp"
#include "Weapon.hpp"

HandsRequiredItemFilter::HandsRequiredItemFilter(const EquipmentWornLocation ewl, const int hands_avail)
: hands_available(hands_avail), slot_location(ewl)
{
}

// Check to see if the item can be wielded.
bool HandsRequiredItemFilter::passes_filter(ItemPtr item) const
{
  bool passes = false;

  // Can't equip anything if your hands are full!
  if (item && (hands_available > 0))
  {
    int hands_required = item->get_hands_required();
    passes = ((hands_required == 1) || (hands_required <= hands_available));

    // Two-handed weapons can't be wielded in the off-hand.
    passes = passes && ((hands_required == 1) || (slot_location == EquipmentWornLocation::EQUIPMENT_WORN_WIELDED));
  }

  return passes;
}

#ifdef UNIT_TESTS
#include "unit_tests/HandsRequiredItemFilter_test.cpp"
#endif


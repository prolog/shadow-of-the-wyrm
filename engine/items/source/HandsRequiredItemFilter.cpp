#include "HandsRequiredItemFilter.hpp"
#include "Weapon.hpp"

HandsRequiredItemFilter::HandsRequiredItemFilter(const int hands_avail)
: hands_available(hands_avail)
{
}

// Check to see if the item can be wielded.
bool HandsRequiredItemFilter::passes_filter(ItemPtr item) const
{
  bool passes = false;

  // Can't equip anything if your hands are full!
  if (item && (hands_available > 0))
  {
    passes = (item->get_hands_required() <= hands_available);
  }

  return passes;
}

#ifdef UNIT_TESTS
#include "unit_tests/HandsRequiredItemFilter_test.cpp"
#endif


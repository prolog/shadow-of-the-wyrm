#pragma once
#include "IItemFilter.hpp"

// A filter that passes if the item is not a weapon, or if it is a weapon,
// if it can be wielded with the number of hands available.
class HandsRequiredItemFilter : public IItemFilter
{
  public:
    HandsRequiredItemFilter(const int num_hands_avail);

    bool passes_filter(ItemPtr item) const override;

  protected:
    int hands_available;
};


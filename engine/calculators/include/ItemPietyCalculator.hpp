#pragma once
#include "Item.hpp"

// Class used to determine how much piety should be granted for sacrificing
// a particular item to one of the deities.
class ItemPietyCalculator
{
  public:
    int calculate_piety(ItemPtr item);

  protected:
    // The minimum piety required before calculate_piety will return a non-zero
    // value.  Deities don't like pitiful offerings.
    static const int MINIMUM_PIETY;
};


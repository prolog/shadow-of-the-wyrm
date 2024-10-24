#pragma once
#include "Item.hpp"

// Class used to determine how much piety should be granted for sacrificing
// a particular item to one of the deities.
class ItemPietyCalculator
{
  public:
    int calculate_piety(ItemPtr item);

  protected:
    friend class ItemPietyCalculatorTestFixture;

    float get_corpse_level_multiplier(ItemPtr item);

    int get_base_value(ItemPtr item);
    int get_base_divisor(ItemPtr item);

    // The minimum piety required before calculate_piety will return a non-zero
    // value.  Deities don't like pitiful offerings.
    static const int MINIMUM_PIETY;

    // How much nutrition does something have before it can be considered for
    // piety?  E.g., silverweed is very nutritious, and is fine; corpses are
    // also fine; harvested fish doesn't meet the requirements.
    static const int MINIMUM_NUTRITION_FOR_PIETY;

    // The base divisor to arrive at piety - used for most items (all but
    // corpses, which deities especially like).
    static const int BASE_DIVISOR;

    // The divisor used for corpses, which are appreciated by deities more
    // than any other item.
    static const int CORPSE_DIVISOR;

    // The Nine still appreciate monetary gifts.
    static const int CURRENCY_DIVISOR;

    // Artifacts are valuable, and are reflected as such in the piety 
    // calculations.
    static const int ARTIFACT_DIVISOR;

    static const float CORPSE_PIETY_BASE_MULTIPLIER;
};


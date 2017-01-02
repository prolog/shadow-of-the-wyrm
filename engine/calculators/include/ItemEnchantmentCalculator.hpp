#pragma once
#include "ItemTypes.hpp"

// Calculation class used to determine how many enchantments an item
// should get, based on the current danger level.  This is not a fixed
// number; it will be randomly calculated.
class ItemEnchantmentCalculator
{
  public:
    int calculate_enchantments(const int danger_level);
    int calculate_pct_chance_brand(const float pct_chance_multiplier, const bool brandable, const bool artifact);

  protected:
    static const int BASE_CHANCE_BRAND;
};


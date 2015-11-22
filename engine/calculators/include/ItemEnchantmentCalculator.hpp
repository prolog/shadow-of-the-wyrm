#pragma once

// Calculation class used to determine how many enchantments an item
// should get, based on the current danger level.  This is not a fixed
// number; it will be randomly calculated.
class ItemEnchantmentCalculator
{
  public:
    int calculate_enchantments(const int danger_level);
};


#pragma once
#include <utility>
#include "Item.hpp"

class ItemBreakageCalculator
{
  public:
    int calculate_pct_chance_digging_breakage(ItemPtr item);

  protected:
    std::pair<bool, int> get_override_pct_chance_breakage(ItemPtr item);

    static const int BASE_PCT_CHANCE_DIGGING_BREAKAGE;
};


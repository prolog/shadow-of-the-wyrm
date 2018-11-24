#pragma once
#include <utility>
#include "Creature.hpp"
#include "Item.hpp"

class ItemBreakageCalculator
{
  public:
    int calculate_pct_chance_digging_breakage(CreaturePtr creature, TilePtr tile, ItemPtr item);
    float calculate_skill_breakage_multiplier(CreaturePtr creature);
    float calculate_tile_breakage_multiplier(TilePtr tile);

  protected:
    std::pair<bool, int> get_override_pct_chance_breakage(ItemPtr item);

    static const int BASE_PCT_CHANCE_DIGGING_BREAKAGE;
    static const float MIN_SKILL_BREAKAGE_MULTIPLIER;
};


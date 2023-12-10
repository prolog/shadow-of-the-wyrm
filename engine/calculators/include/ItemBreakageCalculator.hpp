#pragma once
#include <utility>
#include "Creature.hpp"
#include "Item.hpp"

class ItemBreakageCalculator
{
  public:
    int calculate_pct_chance_digging_breakage(CreaturePtr creature, TilePtr tile, ItemPtr item) const;
    float calculate_skill_breakage_multiplier(CreaturePtr creature) const;
    float calculate_tile_breakage_multiplier(TilePtr tile) const;
    float get_status_breakage_multiplier(const ItemStatus item_status) const;

  protected:
    std::pair<bool, int> get_override_pct_chance_breakage(ItemPtr item) const;

    static const int BASE_PCT_CHANCE_DIGGING_BREAKAGE;
    static const float MIN_SKILL_BREAKAGE_MULTIPLIER;
};


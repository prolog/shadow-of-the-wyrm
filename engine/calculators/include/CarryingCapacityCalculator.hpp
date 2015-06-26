#pragma once
#include "Creature.hpp"

class CarryingCapacityCalculator
{
  public:
    CarryingCapacityCalculator();

    // Calculate the total number of items that can be carried.
    uint calculate_carrying_capacity_total_items(CreaturePtr creature);

  protected:
    const uint CARRYING_CAPACITY_TOTAL_ITEMS_MULTIPLIER;
    const std::map<CreatureSize, float> carrying_capacity_multipliers;
};


#pragma once
#include "Creature.hpp"

class CarryingCapacityCalculator
{
  public:
    CarryingCapacityCalculator();

    // Calculate the total number of items that can be carried.
    uint calculate_carrying_capacity_total_items(CreaturePtr creature) const;
    
    // Calculate the weight at which a creature becomes burdened.
    uint calculate_burdened_weight(CreaturePtr creature) const;

    // Calculate the weight at which a creature becomes strained.
    uint calculate_strained_weight(CreaturePtr creature) const;

    // Calculate the weight at which a creature becomes overburdened.
    uint calculate_overburdened_weight(CreaturePtr creature) const;

  protected:
    const uint CARRYING_CAPACITY_TOTAL_ITEMS_MULTIPLIER;
    const std::map<CreatureSize, float> carrying_capacity_multipliers;
};


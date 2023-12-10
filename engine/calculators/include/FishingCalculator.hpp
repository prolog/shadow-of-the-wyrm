#pragma once
#include "Creature.hpp"
#include "WaterTypes.hpp"

class FishingCalculator
{
  public:
    std::vector<std::pair<FishingOutcomeType, int>> calculate_fishing_outcomes(CreaturePtr creature) const;

    int get_item_status_outcome_modifier(const ItemPtr wielded_item) const;
};


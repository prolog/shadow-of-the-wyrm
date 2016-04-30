#pragma once
#include "Creature.hpp"
#include "WaterTypes.hpp"

class FishingCalculator
{
  public:
    std::vector<std::pair<FishingOutcomeType, int>> calculate_fishing_outcomes(CreaturePtr creature);
    
};


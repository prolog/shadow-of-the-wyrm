#pragma once
#include "Creature.hpp"

// Weaving allows the creation of new items of clothing from fibres.
// Unlike skinning, which just provides a straight evade or soak bonus,
// weaving provides a randomized number of free enchants based on the
// creature's Weaving skill.
class WeavingCalculator
{
  public:
    int calculate_min_enchant_points(CreaturePtr creature);
    int calculate_max_enchant_points(CreaturePtr creature);
};


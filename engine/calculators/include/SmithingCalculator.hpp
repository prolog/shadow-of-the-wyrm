#pragma once
#include <vector>
#include "Creature.hpp"

// Calculator used when improving items at a forge with Smithing.
class SmithingCalculator
{
  public:
    std::vector<int> calculate_pct_chances_extra_point(CreaturePtr creature, const SkillType primary_crafting_skill);    
};


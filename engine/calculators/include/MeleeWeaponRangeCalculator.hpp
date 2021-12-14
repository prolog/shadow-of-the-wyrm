#pragma once
#include "Creature.hpp"

class MeleeWeaponRangeCalculator
{
  public:
    int get_primary_melee_range(CreaturePtr creature) const;
};


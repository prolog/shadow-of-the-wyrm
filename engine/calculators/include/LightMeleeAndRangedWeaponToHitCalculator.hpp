#pragma once
#include "ToHitCalculator.hpp"

class LightMeleeAndRangedWeaponToHitCalculator : public ToHitCalculator
{
  public:
    LightMeleeAndRangedWeaponToHitCalculator();
    int calculate(CreaturePtr creature);
};

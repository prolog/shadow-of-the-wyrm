#pragma once
#include "ToHitCalculator.hpp"

class HeavyWeaponToHitCalculator : public ToHitCalculator
{
  public:
    HeavyWeaponToHitCalculator();
    int calculate(CreaturePtr creature);
};

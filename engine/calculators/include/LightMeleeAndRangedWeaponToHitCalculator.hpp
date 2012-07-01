#pragma once
#include "ToHitCalculator.hpp"

class LightMeleeAndRangedWeaponToHitCalculator : public ToHitCalculator
{
  public:
    LightMeleeAndRangedWeaponToHitCalculator();
    LightMeleeAndRangedWeaponToHitCalculator(const AttackType attack_type);
    
    int calculate(CreaturePtr creature);
};

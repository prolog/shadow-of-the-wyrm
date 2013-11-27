#pragma once
#include "ToHitCalculator.hpp"

class HeavyWeaponToHitCalculator : public ToHitCalculator
{
  public:
    HeavyWeaponToHitCalculator();
    HeavyWeaponToHitCalculator(const AttackType attack_type);
    
    int calculate(CreaturePtr creature) override;
};
